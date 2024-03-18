#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace engine
{
	class RotatorComponent : public BaseComponent
	{
	public:
		RotatorComponent(engine::GameObject* pOwner, const glm::vec3& origin, float radius = 10.f, float speed = 50.f);
		virtual ~RotatorComponent() = default;

		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		void Awake() override {};
		void Update() override;
	private:
		glm::vec3 m_Origin;
		float m_Radius;
		float m_Speed;
		float m_Angle{};
		
	};
}


