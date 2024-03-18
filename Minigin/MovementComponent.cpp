#include "MovementComponent.h"
#include "GameObject.h"

engine::MovementComponent::MovementComponent(engine::GameObject* pOwner, float maxMovementSpeed)
	: BaseComponent(pOwner)
	, m_MaxMovementSpeed{ maxMovementSpeed }
{
}

void engine::MovementComponent::Update()
{
	if (m_MovementDirection.x != 0.f ||
		m_MovementDirection.y != 0.f)
	{
		auto worldPos{ GetOwner()->GetWorldPosition() };
		worldPos += m_MovementDirection * m_MaxMovementSpeed * deltaTime;
		auto nextPos{ GetOwner()->GetWorldPosition() + (m_MovementDirection * m_MaxMovementSpeed * deltaTime) };
		GetOwner()->SetLocalPosition(nextPos);
		m_MovementDirection = {};
	}
	
}

