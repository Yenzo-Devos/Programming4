#include "IdleState.h"
#include "SpriteComponent.h"

void game::IdleState::Update(float)
{
}

game::PlayerState* game::IdleState::HandleInput(game::PlayerComponent& playerComp)
{
	if (playerComp.GetOwner()->GetWorldPosition() != m_LastPos)
		// return MoveState

	m_LastPos = playerComp.GetOwner()->GetWorldPosition();
	return nullptr;
}

void game::IdleState::OnEnter(game::PlayerComponent& playerComp)
{
	playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("idle");
	m_LastPos = playerComp.GetOwner()->GetWorldPosition();
}
