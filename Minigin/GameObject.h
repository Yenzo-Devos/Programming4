#pragma once
#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <stdexcept>

#include "Transform.h"

namespace dae
{
	class Texture2D;
	class BaseComponent;
	// todo: this should become final.
	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void Render() const;

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//glm::vec3 GetLocation() const { return m_transform.GetPosition(); }
		bool GetIsDead() { return m_IsDead; }

		// parent children functions
		void SetParent(GameObject* parent);
		GameObject* GetParent() const { return m_pParent; }
		size_t GetChildCount() const { return m_pChildren.size(); }
		GameObject* GetChildAt(unsigned int index) const { return m_pChildren[index]; }

		// position functions
		void SetLocalPos(const glm::vec3& pos);
		const glm::vec3& GetWorldPos();
		void UpdateWorldPos();

	private:
		bool m_IsDead{ false };
		//Transform m_transform{};
		std::vector<dae::BaseComponent*> m_pComponentVec;

		std::vector<GameObject*> m_pChildren;
		GameObject* m_pParent;

		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;

		// parent children functions
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
		bool IsChild(GameObject* pParent);

		// position function && vars
		bool m_IsPosDirty{ false };
		void SetPositionDirty() { m_IsPosDirty = true; }

		// Everything component template related
	public:
		template<typename Component>
		Component* AddComponent()
		{
			if (std::is_base_of<BaseComponent, Component>::value)
			{
				Component* tempComp{ new Component(this) };
				m_pComponentVec.push_back(tempComp);
				return tempComp;
			}
			else
				throw std::runtime_error("component added has no correct baseComponent");
		}

		template<typename Component>
		Component* GetComponent() const
		{
			Component* tempComp;
			for (auto component : m_pComponentVec)
			{
				tempComp = dynamic_cast<Component*>(component);
				if (tempComp)
					return tempComp;
			}
			throw std::runtime_error("component not found in gameobject");
		}

		template<typename Component>
		void RemoveComponent() const
		{
			Component* tempComp;
			for (int index{}; index < m_pComponentVec.size; ++index)
			{
				tempComp = dynamic_cast<Component*>(m_pComponentVec[index]);
				if (tempComp)
				{
					delete m_pComponentVec[index];
					m_pComponentVec[index] = nullptr;
				}
			}
		}

		template<typename Component>
		bool HasComponent()
		{
			Component* tempComp;
			for (auto component : m_pComponentVec)
			{
				tempComp = dynamic_cast<Component*>(component);
				if (tempComp)
					return true;
			}
			return false;
		}
	};
}
