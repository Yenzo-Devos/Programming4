#pragma once
#include "BaseComponent.h"
#include "glm/glm.hpp"
namespace engine
{
	class GameObject;

	class MovementComponent : public BaseComponent
	{
	public:
		MovementComponent(engine::GameObject* pOwner, float maxMovementSpeed);
		virtual ~MovementComponent() = default;

		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;

		void Awake() override {};
		void Update(float deltaTime) override;
		
		void SetMaxMovementSpeed(float newMaxMovementSpeed) { m_MaxMovementSpeed = newMaxMovementSpeed; }
		void SetMovementDirection(glm::vec3 newMovementDirection) { m_MovementDirection = newMovementDirection; }
		
	private:
		glm::vec3 m_MovementDirection{};
		float m_MaxMovementSpeed{};
	};
}


