#include "EnemyComponent.h"
#include "EnemyChaseState.h"

game::EnemyComponent::EnemyComponent(dae::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_pState{ std::make_unique<EnemyChaseState>(pOwner->GetComponent<dae::SpriteComponent>(), pOwner->GetComponent<ChaseComponent>()) }
{
}

void game::EnemyComponent::Update(float deltaTime)
{
	m_pState->Update(deltaTime);
	HandleState();
}

void game::EnemyComponent::HandleState()
{
	auto newState = m_pState->HandleState(*m_pOwner);
	if (newState != nullptr)
	{
		m_pState->OnExit(*m_pOwner);
		m_pState = std::move(newState);
		m_pState->OnEnter(*m_pOwner);
	}
}

void game::EnemyComponent::Broadcast(dae::GameObject*, dae::Event event)
{
	switch (event)
	{
	case dae::Event::OnPlayerDeath:
		break;
	case dae::Event::OnPlayerScored:
		break;
	case dae::Event::OnIngredientFallOnPlate:
		break;
	case dae::Event::EnemyStunned:
	{
		auto chaseState = dynamic_cast<EnemyChaseState*>(m_pState.get());
		if (chaseState) chaseState->Stun();
		break;
	}
	default:
		break;
	}
}
