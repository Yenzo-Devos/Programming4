#include "PlayerComponent.h"
#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "PepperComponent.h"

game::PlayerComponent::PlayerComponent(dae::GameObject* pOwner, dae::GameObject* pPepper)
	: BaseComponent( pOwner )
	, m_pState{ std::make_unique<PlayerIdleState>() }
	, m_pPepper{ pPepper }
{
}

void game::PlayerComponent::Update(float deltaTime)
{
	m_pState->Update(deltaTime);
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

void game::PlayerComponent::ActivatePepper(glm::vec2 pos, glm::vec2 dir)
{
	if (m_pPepper->GetComponent<PepperComponent>()->Activate(pos, dir))
	{
		auto moveState = dynamic_cast<PlayerMoveState*>(m_pState.get());
		if (moveState) moveState->Throw();
	}
}
