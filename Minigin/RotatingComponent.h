#pragma once
#include "BaseComponent.h"
#include <glm.hpp>
namespace dae
{

	class RotatingComponent final : public BaseComponent
	{
	public:
		RotatingComponent(GameObject* owner, glm::vec3 origin, float radius, float speed);
		~RotatingComponent() = default;

		RotatingComponent(const RotatingComponent& other) = delete;
		RotatingComponent(RotatingComponent&& other) = delete;
		RotatingComponent& operator=(const RotatingComponent& other) = delete;
		RotatingComponent& operator=(RotatingComponent&& other) = delete;

		virtual void Update(float deltaTime) override;

	private:
		const glm::vec3 m_Origin{};
		float m_Radius{};
		float m_Speed{};
		float m_Angle{};
	};
}


