#include "GameCommand.h"
#include "LivesComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
#include "SceneManager.h"
#include "Scene.h"
#include "HitboxComponent.h"
#include "CollisionHandler.h"
#include "PlayerComponent.h"
#include "PlayerState.h"
#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "PlayerPepperState.h"
#include "PlayerDyingState.h"
#include "PlayerWinningState.h"

#include <ranges>
#include <memory>

game::MoveCommand::MoveCommand(dae::GameObject* pGameObject, float speed, glm::vec3 direction)
	: GameObjectCommand(pGameObject)
	, m_Speed{ speed }
	, m_Direction{ direction }
{
}

void game::MoveCommand::Execute(float deltaTime)
{
	if (m_Direction.y != 0)
		Climb(deltaTime);
	else if (m_Direction.x != 0)
		Walk(deltaTime);
}

void game::MoveCommand::Climb(float deltaTime)
{
	// check if overlapping with ladder
	auto ladderVec = dae::SceneManager::GetInstance().GetActiveScene().GetAllObjectByTag("ladder");
	auto playerHitboxComp = GetGameObject()->GetComponent<dae::HitboxComponent>();
	
	for (auto ladder : ladderVec)
	{
		// clean up by simplifying
		auto ladderHitbox = ladder->GetComponent<dae::HitboxComponent>()->GetHitbox("main_hitbox");
		if (dae::CollisionHandler::GetInstance().IsOverlapping(playerHitboxComp->GetHitbox("feet_hitbox"), ladderHitbox) and
			GetGameObject()->GetWorldPosition().x == ladder->GetWorldPosition().x or
			dae::CollisionHandler::GetInstance().IsOverlapping(playerHitboxComp->GetHitbox("body_hitbox"), ladderHitbox) and
			GetGameObject()->GetWorldPosition().x == ladder->GetWorldPosition().x)
		{
			GetGameObject()->SetLocalPosition(GetGameObject()->GetWorldPosition() + (m_Direction * m_Speed * deltaTime));
			
			if (GetGameObject()->HasComponent<game::PlayerComponent>())
			{
				auto playerComp = GetGameObject()->GetComponent<game::PlayerComponent>();
				// change state to move and give direction
				playerComp->ChangeDirection(m_Direction);
			}
			return;
		}
	}
}

void game::MoveCommand::Walk(float deltaTime)
{
	//GetGameObject()->GetWorldPosition() + (m_Direction * m_Speed * deltaTime)
	
	// clean this up
	auto playerHitbox = GetGameObject()->GetComponent<dae::HitboxComponent>()->GetHitbox("feet_hitbox");
	auto bufferHitbox = playerHitbox;
	bufferHitbox->left += static_cast<int>(m_Direction.x * m_Speed * deltaTime);
	
	auto walkableObjectVec = dae::SceneManager::GetInstance().GetActiveScene().GetAllObjectByTag("walkable_object");
	for (auto walkableObject : walkableObjectVec)
	{
		auto hitbox = walkableObject->GetComponent<dae::HitboxComponent>()->GetHitbox("main_hitbox");
		if (dae::CollisionHandler::GetInstance().IsFullyOverlapping(bufferHitbox, hitbox))
		{
			GetGameObject()->SetLocalPosition(GetGameObject()->GetWorldPosition() + (m_Direction * m_Speed * deltaTime));
			
			if (GetGameObject()->HasComponent<game::PlayerComponent>())
			{
				auto playerComp = GetGameObject()->GetComponent<game::PlayerComponent>();
				// change state to move and give direction
				playerComp->ChangeDirection(m_Direction);
			}
			return;
		}
	}
}

game::KillCommand::KillCommand(dae::GameObject* pGameObject)
	: GameObjectCommand(pGameObject)
{
}

void game::KillCommand::Execute(float)
{
	//if (GetGameObject()->HasComponent<LivesComponent>())
	GetGameObject()->GetComponent<LivesComponent>()->LoseLife(1);

	auto& ss = dae::ServiceLocator::GetSoundSystem();
	dae::AudioFile deathAudio{ "../Data/sounds/Death.wav", "Death", 0 };
	ss.AddToQueue(deathAudio);
}

game::ThrowPepperCommand::ThrowPepperCommand(dae::GameObject* pGameObject)
	: GameObjectCommand(pGameObject)
{
}

void game::ThrowPepperCommand::Execute(float)
{
	// get direction
	auto playerComp = GetGameObject()->GetComponent<game::PlayerComponent>();
	glm::vec3 direction = playerComp->GetDirection();


	// create pepper Object

	// set player to pepperState
	// change state to pepper and give direction
	//playerComp->ChangeState(&game::PlayerState::m_Pepper);
}
