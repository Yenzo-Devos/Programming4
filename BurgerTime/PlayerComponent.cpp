#include "PlayerComponent.h"

game::PlayerComponent::PlayerComponent(dae::GameObject* pOwner)
	: BaseComponent( pOwner )
{
}

void game::PlayerComponent::Update(float elapsedSec)
{
	m_pState->Update(elapsedSec);
	HandleInput();
}

void game::PlayerComponent::HandleInput()
{
	PlayerState* newState = m_pState->HandleInput(*this);
	if (newState != nullptr)
	{
		m_pState->OnExit(*this);
		m_pState = newState;
		m_pState->OnEnter(*this);
	}
}
