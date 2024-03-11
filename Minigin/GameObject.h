#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include <vector>
#include <memory>
#include <concepts>

namespace engine
{
	template<typename ComponentType>
	concept ComponentCon = requires(ComponentType c)
	{
		{std::is_base_of<BaseComponent, ComponentType>::value };
	};
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		
		void FixedUpdate(float fixedDeltaTime);
		void Update(float deltaTime);
		void Render() const;

		void RemoveDeadComponents();

		GameObject* GetParent() const { return m_pParent; }
		void SetParent(GameObject* pParent, bool keepWorldPosition);
		int GetChildCount() const { return int(m_pChildren.size()); }
		GameObject* GetChildAt(int index) const;

		void SetLocalPosition(glm::vec3 position);
		void UpdateWorldPositon();
		glm::vec3 GetWorldPosition();

	private:
		//engine::Transform m_Transform{};
		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
		std::vector<std::unique_ptr<BaseComponent>> m_pComponentVector;

		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren;

		bool m_IsPositionDirty{ false };

		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
		bool IsChild(GameObject* pParent);

		void SetPositionDirty();

	public:
		template<ComponentCon ComponentType, typename... Args>
		void AddComponent(const Args&... args)
		{
			auto component{ std::make_unique<ComponentType>(this, args...) };
			bool componentAdded{ false };
			for (int componentIndex{ 0 }; componentIndex < int(m_pComponentVector.size()); ++componentIndex)
			{
				if (m_pComponentVector[componentIndex].get())
					continue;

				m_pComponentVector[componentIndex] = std::move(component);
				componentAdded = true;
				break;
			}

			if (!componentAdded)
			{
				auto& newComp{ m_pComponentVector.emplace_back(std::move(component)) };
				newComp->Awake();
			}
		}

		template<ComponentCon ComponentType>
		ComponentType* GetComponent()
		{
			for (auto&& comp : m_pComponentVector)
			{
				auto pCast = dynamic_cast<ComponentType*>(comp.get());
				if (pCast)
					return pCast;
			}
			return nullptr;
		}
	};
}
