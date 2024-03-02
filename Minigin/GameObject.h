#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include <vector>
#include <memory>
#include <concepts>

namespace dae
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
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		
		virtual void FixedUpdate(float fixedDeltaTime);
		virtual void Update(float deltaTime);
		virtual void Render() const;

		void SetPosition(float x, float y);
		glm::vec3 GetPosition() const { return m_Transform.GetPosition(); }

		void RemoveDeadComponents();

	private:
		dae::Transform m_Transform{};
		std::vector<std::unique_ptr<BaseComponent>> m_pComponentVector;

	public:
		template<ComponentCon ComponentType, typename... Args>
		void AddComponent(const Args&... args)
		{
			auto component{ std::make_unique<ComponentType>(this, args...) };
			bool componentAdded{ false };
			for (int componentIndex{ 0 }; componentIndex < m_pComponentVector.size(); ++componentIndex)
			{
				if (m_pComponentVector[componentIndex].get())
					continue;

				m_pComponentVector[componentIndex] = std::move(component);
				m_pComponentVector[componentIndex]->SetOwner(this);
				componentAdded = true;
				break;
			}

			if (!componentAdded)
			{
				auto& newComp{ m_pComponentVector.emplace_back(std::move(component)) };
				newComp->SetOwner(this);
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
