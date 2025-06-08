#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "SpriteComponent.h"

std::unique_ptr<game::PlayerState> game::PlayerIdleState::HandleState(PlayerComponent& playerComp)
{
	if (playerComp.GetOwner()->GetWorldPosition() != m_LastPos)
		return std::make_unique<PlayerMoveState>();

	return nullptr;
}

void game::PlayerIdleState::OnEnter(PlayerComponent& playerComp)
{
	m_LastPos = playerComp.GetOwner()->GetWorldPosition();
	playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("idle");
}
