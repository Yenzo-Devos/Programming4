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
#include "IngredientComponent.h"

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
	auto nextPos = GetGameObject()->GetWorldPosition() + (m_Direction * m_Speed * deltaTime);
	if (dae::CollisionHandler::GetInstance().IsNextClimbPossible(nextPos, GetGameObject()->GetDimensions().second))
	{
		GetGameObject()->SetLocalPosition(GetGameObject()->GetWorldPosition() + (m_Direction * m_Speed * deltaTime));

		if (GetGameObject()->HasComponent<game::PlayerComponent>())
		{
			auto playerComp = GetGameObject()->GetComponent<game::PlayerComponent>();
			playerComp->ChangeDirection(m_Direction);

			auto ingredientVec = dae::CollisionHandler::GetInstance().PerformIngredientCheck(GetGameObject()->GetComponent<dae::HitboxComponent>()->GetHitbox("feet_hitbox"));
			if (!ingredientVec.empty())
				for (const auto& ingredient : ingredientVec)
					ingredient.first->GetComponent<IngredientComponent>()->Hit(ingredient.second);
		}
	}
}

void game::MoveCommand::Walk(float deltaTime)
{
	// clean this up
	auto nextPos = GetGameObject()->GetWorldPosition() + (m_Direction * m_Speed * deltaTime);
	auto dimensions = GetGameObject()->GetDimensions();
	if (dae::CollisionHandler::GetInstance().IsNextWalkPossible(nextPos, dimensions.first, dimensions.second))
	{
		GetGameObject()->SetLocalPosition(GetGameObject()->GetWorldPosition() + (m_Direction * m_Speed * deltaTime));
		if (GetGameObject()->HasComponent<game::PlayerComponent>())
		{
			auto playerComp = GetGameObject()->GetComponent<game::PlayerComponent>();
			playerComp->ChangeDirection(m_Direction);
			
			// check for ingredient overlap
			auto ingredientVec = dae::CollisionHandler::GetInstance().PerformIngredientCheck(GetGameObject()->GetComponent<dae::HitboxComponent>()->GetHitbox("feet_hitbox"));
			if (!ingredientVec.empty())
				for (const auto& ingredient : ingredientVec)
					ingredient.first->GetComponent<IngredientComponent>()->Hit(ingredient.second);
		}
		return;
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
	glm::vec3 playerPos = GetGameObject()->GetWorldPosition();
	
	glm::vec2 pos{};
	if (direction.x == 1.f)
		pos = { playerPos.x + GetGameObject()->GetDimensions().first, playerPos.y };
	else if (direction.x == -1.f)
		pos = { playerPos.x - GetGameObject()->GetDimensions().first, playerPos.y };
	else return;
	
	playerComp->ActivatePepper(pos, direction);
	// set player to pepperState
	// change state to pepper and give direction
	//playerComp->ChangeState(&game::PlayerState::m_Pepper);
}
