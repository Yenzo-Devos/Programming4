#include "Command.h"
#include "LivesComponent.h"

dae::GameObjectCommand::GameObjectCommand(GameObject* pGameObject)
	: Command()
	, m_pGameObject{ pGameObject }
{
}

dae::MoveCommand::MoveCommand(GameObject* pGameObject, float speed, glm::vec3 direction)
	: GameObjectCommand(pGameObject)
	, m_Speed{ speed }
	, m_Direction{ direction }
{
}

void dae::MoveCommand::Execute(float deltaTime)
{
	GetGameObject()->SetLocalPosition(GetGameObject()->GetWorldPosition() + (m_Direction * m_Speed * deltaTime));
}

dae::KillCommand::KillCommand(GameObject* pGameObject)
	:GameObjectCommand(pGameObject)
{
}

void dae::KillCommand::Execute(float)
{
	//if (GetGameObject()->HasComponent<LivesComponent>())
	GetGameObject()->GetComponent<LivesComponent>()->LoseLife(1);
}