#pragma once
#include <memory>
#include <vector>
#include <stdexcept>
#include <glm.hpp>

#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float fixedDeltaTime);

		void SetDead();
		bool GetIsDead() { return m_IsDead; }

		// scenegraph function
		GameObject* GetParent() { return m_pParent; }
		void SetParent(GameObject* pParent, bool keepWorldPos);
		int GetChildCount() { return static_cast<int>(m_pChildren.size()); }
		GameObject* GetChildAt(int index) { return m_pChildren[index]; }

		// position functions
		const glm::vec3& GetWorldPosition();
		void SetLocalPosition(const glm::vec3& pos);
		void UpdateWorldPosition();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool m_IsDead{ false };
		bool m_HasDeadComponent{ false };

		std::vector<std::unique_ptr<BaseComponent>> m_ComponentVec{};

		// scenegraph member vars
		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren{};

		// scenegraph function
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
		bool IsChild(GameObject* pParent);

		// position member vars
		bool m_IsPositionDirty{ false };
		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};

		// position function
		void SetPositionDirty();
	
	// templated component functions
	public:
		template <typename Comp, typename... Args>
		void AddComponent(Args&&... args)
		{
			if (std::is_base_of<BaseComponent, Comp>::value)
			{
				auto comp = std::make_unique<Comp>(this, std::forward<Args>(args)...);
				m_ComponentVec.emplace_back(std::move(comp));
			}
			else
				throw std::runtime_error("T must inherit from BaseComponent");
			
		}

		template <typename Comp>
		void RemoveComponent()
		{
			Comp* tempComp;
			for (int index{}; index < m_ComponentVec.size(); ++index)
			{
				tempComp = dynamic_cast<Comp*>(m_ComponentVec[index].get());
				if (tempComp)
				{
					tempComp->SetDead();
					m_HasDeadComponent = true;
				}
			}
		}

		template <typename Comp>
		Comp* GetComponent()
		{
			Comp* tempComp;
			for (auto& comp : m_ComponentVec)
			{
				tempComp = dynamic_cast<Comp*>(comp.get());
				if (tempComp)
					return tempComp;
			}
			throw std::runtime_error("component not found");
		}

		template <typename Comp>
		bool HasComponent()
		{
			Comp* tempComp;
			for (auto& comp : m_ComponentVec)
			{
				tempComp = dynamic_cast<Comp*>(comp.get());
				if (tempComp)
					return true;
			}
			return false;
		}
	};
}
