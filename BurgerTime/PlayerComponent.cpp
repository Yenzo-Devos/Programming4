#include "PlayerComponent.h"
#include "PlayerIdleState.h"

game::PlayerComponent::PlayerComponent(dae::GameObject* pOwner)
	: BaseComponent( pOwner )
	, m_pState{ new PlayerIdleState() }
{
}

void game::PlayerComponent::Update(float elapsedSec)
{
	m_pState->Update(elapsedSec);
	HandleState();
}

void game::PlayerComponent::HandleState()
{
	PlayerState* newState = m_pState->HandleState(*this);
	if (newState != nullptr)
	{
		m_pState->OnExit(*this);
		m_pState = newState;
		m_pState->OnEnter(*this);
	}
}

void game::PlayerComponent::ChangeState(PlayerState* state)
{
	if (m_pState != state)
		m_pState = state;
}

void game::PlayerComponent::ChangeDiretion(glm::vec3 direction)
{
	if (m_Direction != direction)
		m_Direction = direction;
}
