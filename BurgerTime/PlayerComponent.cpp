#include "PlayerComponent.h"
#include "PlayerIdleState.h"

game::PlayerComponent::PlayerComponent(dae::GameObject* pOwner)
	: BaseComponent( pOwner )
	, m_pState{ std::make_unique<PlayerIdleState>() }
{
}

void game::PlayerComponent::Update(float elapsedSec)
{
	m_pState->Update(elapsedSec);
	HandleState();
}

void game::PlayerComponent::HandleState()
{
	auto newState = m_pState->HandleState(*this);
	if (newState != nullptr)
	{
		m_pState->OnExit(*this);
		m_pState = std::move(newState);
		m_pState->OnEnter(*this);
	}
}

void game::PlayerComponent::ChangeState(std::unique_ptr<PlayerState> state)
{
	if (m_pState != state)
		m_pState = std::move(state);
}

void game::PlayerComponent::ChangeDirection(glm::vec3 direction)
{
	if (m_Direction != direction)
		m_Direction = direction;
}

bool game::PlayerComponent::CheckIfPlayerMoved() const
{
	if (m_pOwner->GetWorldPosition() != m_LastPos) 
		return true;
	return false;
}
