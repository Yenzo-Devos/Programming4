#include "PlayerMoveState.h"
#include "PlayerComponent.h"
#include "PlayerIdleState.h"
#include "SpriteComponent.h"

std::unique_ptr<game::PlayerState> game::PlayerMoveState::HandleState(PlayerComponent& playerComp)
{
	if (playerComp.GetOwner()->GetWorldPosition() == m_LastPos)
		return std::make_unique<PlayerIdleState>();

	m_LastPos = playerComp.GetOwner()->GetWorldPosition();
	return nullptr;
}

void game::PlayerMoveState::OnEnter(PlayerComponent& playerComp)
{
	// change animation based on direction
	ChangeDirection(playerComp.GetDirection());
	if (m_Direction.x == 1.f)
		playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("walkRight");
	else if (m_Direction.x == -1.f)
		playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("walkLeft");
	else if (m_Direction.y == 1.f)
		playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("walkDown");
	else if (m_Direction.y == -1.f)
		playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("walkUp");

	m_LastPos = playerComp.GetOwner()->GetWorldPosition();
}

void game::PlayerMoveState::ChangeDirection(glm::vec3 direction)
{
	if (m_Direction != direction)
		m_Direction = direction;
}
