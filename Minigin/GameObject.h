#pragma once
#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Transform.h"

namespace dae
{
	class Texture2D;
	class BaseComponent;
	// todo: this should become final.
	class GameObject 
	{
	public:
		virtual void Update();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		glm::vec3 GetLocation() const { return m_transform.GetPosition(); }

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_texture{};
		std::vector<dae::BaseComponent*> m_pComponentVec;

	public:
		// Everything component template related
		template<typename Component>
		Component* AddComponent()
		{
			if (std::is_base_of(BaseComponent, Component))
			{
				Component* tempComp{ new Component(this) };
				m_pComponentVec.push_back(tempComp);
				return tempComp;
			}
		}
	};
}
