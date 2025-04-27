#include "GameCommand.h"
#include "LivesComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

game::MoveCommand::MoveCommand(dae::GameObject* pGameObject, float speed, glm::vec3 direction)
	: GameObjectCommand(pGameObject)
	, m_Speed{ speed }
	, m_Direction{ direction }
{
}

void game::MoveCommand::Execute(float deltaTime)
{
	GetGameObject()->SetLocalPosition(GetGameObject()->GetWorldPosition() + (m_Direction * m_Speed * deltaTime));
}

game::KillCommand::KillCommand(dae::GameObject* pGameObject)
	:GameObjectCommand(pGameObject)
{
}

void game::KillCommand::Execute(float)
{
	//if (GetGameObject()->HasComponent<LivesComponent>())
	GetGameObject()->GetComponent<LivesComponent>()->LoseLife(1);

	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.Play("Death", 100, 0);
}