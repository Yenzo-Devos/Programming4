#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "PlayerDyingState.h"
#include "SpriteComponent.h"
#include "LivesComponent.h"

std::unique_ptr<game::PlayerState> game::PlayerIdleState::HandleState(dae::GameObject* pOwner)
{
	if (pOwner->GetWorldPosition() != m_LastPos)
		return std::make_unique<PlayerMoveState>();

	if (m_CurrentHealth != pOwner->GetComponent<LivesComponent>()->GetCurrentNrOfLives())
		return std::make_unique<PlayerDyingState>();

	return nullptr;
}

void game::PlayerIdleState::OnEnter(dae::GameObject* pOwner)
{
	m_LastPos = pOwner->GetWorldPosition();
	pOwner->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("idle");
	m_CurrentHealth = pOwner->GetComponent<LivesComponent>()->GetCurrentNrOfLives();
}
