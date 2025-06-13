#include "PlayerMoveState.h"
#include "PlayerComponent.h"
#include "PlayerIdleState.h"
#include "PlayerPepperState.h"
#include "PlayerDyingState.h"
#include "SpriteComponent.h"
#include "LivesComponent.h"

std::unique_ptr<game::PlayerState> game::PlayerMoveState::HandleState(dae::GameObject* pOwner)
{
	if (pOwner->GetWorldPosition() == m_LastPos)
		return std::make_unique<PlayerIdleState>();

	if (m_Throw)
		return std::make_unique<PlayerPepperState>();

	if (m_CurrentHealth != pOwner->GetComponent<LivesComponent>()->GetCurrentNrOfLives())
		return std::make_unique<PlayerDyingState>();

	m_LastPos = pOwner->GetWorldPosition();
	return nullptr;
}

void game::PlayerMoveState::OnEnter(dae::GameObject* pOwner)
{
	// change animation based on direction
	ChangeDirection(pOwner->GetComponent<PlayerComponent>()->GetDirection());
	if (m_Direction.x == 1.f)
		pOwner->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("walkRight");
	else if (m_Direction.x == -1.f)
		pOwner->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("walkLeft");
	else if (m_Direction.y == 1.f)
		pOwner->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("walkDown");
	else if (m_Direction.y == -1.f)
		pOwner->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("walkUp");

	m_LastPos = pOwner->GetWorldPosition();
	m_CurrentHealth = pOwner->GetComponent<LivesComponent>()->GetCurrentNrOfLives();
}

void game::PlayerMoveState::ChangeDirection(glm::vec3 direction)
{
	if (m_Direction != direction)
		m_Direction = direction;
}

void game::PlayerMoveState::Throw()
{
	m_Throw = true;
}
