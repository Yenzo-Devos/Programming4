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

bool game::MoveCommand::Execute(float deltaTime)
{
	if (m_Direction.y != 0.f)
		return Climb(deltaTime);
	else if (m_Direction.x != 0.f)
		return Walk(deltaTime);
	return false;
}

bool game::MoveCommand::Climb(float deltaTime)
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
		return true;
	}
	return false;
}

bool game::MoveCommand::Walk(float deltaTime)
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
		return true;
	}
	return false;
}

game::ThrowPepperCommand::ThrowPepperCommand(dae::GameObject* pGameObject)
	: GameObjectCommand(pGameObject)
{
}

bool game::ThrowPepperCommand::Execute(float)
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
	else return false;
	
	playerComp->ActivatePepper(pos, direction);
	return true;
}
