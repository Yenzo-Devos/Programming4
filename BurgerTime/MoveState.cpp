#include "MoveState.h"
#include "PlayerComponent.h"
#include "IdleState.h"
#include "SpriteComponent.h"

void game::MoveState::Update(float)
{
}

game::PlayerState* game::MoveState::HandleInput(PlayerComponent& playerComp)
{
	if (playerComp.GetOwner()->GetWorldPosition() == m_LastPos)
		return new IdleState();

	m_LastPos = playerComp.GetOwner()->GetWorldPosition();
	return nullptr;
}

void game::MoveState::OnEnter(PlayerComponent& playerComp)
{
	// change animation based on direction
	//playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("idle");
	m_LastPos = playerComp.GetOwner()->GetWorldPosition();
}
