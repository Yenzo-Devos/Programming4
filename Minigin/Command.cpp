#include "Command.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "Time.h"

void command::MoveUp::Execute()
{
	auto gameObject = GetControlledObject();
	auto movementComp = gameObject->GetComponent<engine::MovementComponent>();
	if (!movementComp)
		return;
	float speed = movementComp->GetMaxMovementSpeed();
	auto worldPos{ gameObject->GetWorldPosition() };
	worldPos += m_MoveDirection * speed * engine::Time::GetInstance().GetDeltaTime();
	auto nextPos{ worldPos + (m_MoveDirection * speed * engine::Time::GetInstance().GetDeltaTime()) };
	gameObject->SetLocalPosition(nextPos);
}

void command::MoveDown::Execute()
{
	auto gameObject = GetControlledObject();
	auto movementComp = gameObject->GetComponent<engine::MovementComponent>();
	if (!movementComp)
		return;
	float speed = movementComp->GetMaxMovementSpeed();
	auto worldPos{ gameObject->GetWorldPosition() };
	worldPos += m_MoveDirection * speed * engine::Time::GetInstance().GetDeltaTime();
	auto nextPos{ worldPos + (m_MoveDirection * speed * engine::Time::GetInstance().GetDeltaTime()) };
	gameObject->SetLocalPosition(nextPos);
	// m_MoveDirection = {};
}

void command::MoveLeft::Execute()
{
	auto gameObject = GetControlledObject();
	auto movementComp = gameObject->GetComponent<engine::MovementComponent>();
	if (!movementComp)
		return;
	float speed = movementComp->GetMaxMovementSpeed();
	auto worldPos{ gameObject->GetWorldPosition() };
	worldPos += m_MoveDirection * speed * engine::Time::GetInstance().GetDeltaTime();
	auto nextPos{ worldPos + (m_MoveDirection * speed * engine::Time::GetInstance().GetDeltaTime()) };
	gameObject->SetLocalPosition(nextPos);
}

void command::MoveRight::Execute()
{
	auto gameObject = GetControlledObject();
	auto movementComp = gameObject->GetComponent<engine::MovementComponent>();
	if (!movementComp)
		return;
	float speed = movementComp->GetMaxMovementSpeed();
	auto worldPos{ gameObject->GetWorldPosition() };
	worldPos += m_MoveDirection * speed * engine::Time::GetInstance().GetDeltaTime();
	auto nextPos{ worldPos + (m_MoveDirection * speed * engine::Time::GetInstance().GetDeltaTime()) };
	gameObject->SetLocalPosition(nextPos);
}
