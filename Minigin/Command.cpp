#include "Command.h"
#include "GameObject.h"
#include "MovementComponent.h"

void command::MoveUp::Execute(engine::GameObject* gameObject)
{
	auto movementComp = gameObject->GetComponent<engine::MovementComponent>();
	if (movementComp)
		movementComp->SetMovementDirection(glm::vec3(0.f, -1.f, 0.f));
}

void command::MoveDown::Execute(engine::GameObject* gameObject)
{
	auto movementComp = gameObject->GetComponent<engine::MovementComponent>();
	if (movementComp)
		movementComp->SetMovementDirection(glm::vec3(0.f, 1.f, 0.f));
}

void command::MoveLeft::Execute(engine::GameObject* gameObject)
{
	auto movementComp = gameObject->GetComponent<engine::MovementComponent>();
	if (movementComp)
		movementComp->SetMovementDirection(glm::vec3(-1.f, 0.f, 0.f));
}

void command::MoveRight::Execute(engine::GameObject* gameObject)
{
	auto movementComp = gameObject->GetComponent<engine::MovementComponent>();
	if (movementComp)
		movementComp->SetMovementDirection(glm::vec3(1.f, 0.f, 0.f));
}
