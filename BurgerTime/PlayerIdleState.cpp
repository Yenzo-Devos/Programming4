#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "PlayerDyingState.h"
#include "SpriteComponent.h"
#include "LivesComponent.h"

std::unique_ptr<game::PlayerState> game::PlayerIdleState::HandleState(PlayerComponent& playerComp)
{
	if (playerComp.GetOwner()->GetWorldPosition() != m_LastPos)
		return std::make_unique<PlayerMoveState>();

	if (m_CurrentHealth != playerComp.GetOwner()->GetComponent<LivesComponent>()->GetCurrentNrOfLives())
		return std::make_unique<PlayerDyingState>();

	return nullptr;
}

void game::PlayerIdleState::OnEnter(PlayerComponent& playerComp)
{
	m_LastPos = playerComp.GetOwner()->GetWorldPosition();
	playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("idle");
	m_CurrentHealth = playerComp.GetOwner()->GetComponent<LivesComponent>()->GetCurrentNrOfLives();
}
