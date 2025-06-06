#include "PlayerIdleState.h"
#include "PlayerMoveState.h"

game::PlayerState* game::PlayerIdleState::HandleState(PlayerComponent& playerComp)
{
	if (playerComp.GetOwner()->GetWorldPosition() != m_LastPos)
		return new PlayerMoveState();

	m_LastPos = playerComp.GetOwner()->GetWorldPosition();
	return nullptr;
}

void game::PlayerIdleState::OnEnter(PlayerComponent& playerComp)
{
	m_LastPos = playerComp.GetOwner()->GetWorldPosition();
}
