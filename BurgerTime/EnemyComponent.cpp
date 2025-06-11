#include "EnemyComponent.h"
#include "EnemyChaseState.h"
#include "EnemyStunnedState.h"
#include "PointsComponent.h"


game::EnemyComponent::EnemyComponent(dae::GameObject* pOwner, dae::GameObject* pointEffectObj, int pointMultiplier)
	: BaseComponent(pOwner)
	, m_pState{ std::make_unique<EnemyChaseState>(pOwner->GetComponent<dae::SpriteComponent>(), pOwner->GetComponent<ChaseComponent>()) }
	, m_pPointEffectObj{ std::move(pointEffectObj) }
	, m_PointMultiplier{ pointMultiplier }
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

void game::EnemyComponent::StartFalling(dae::GameObject* pLastInteractedObj, bool isFirst, int nrOfEnemiesFalling)
{
	auto state = dynamic_cast<EnemyChaseState*>(m_pState.get());
	if (state)
		state->Fall(pLastInteractedObj, isFirst, nrOfEnemiesFalling);
	else if (auto stunState = dynamic_cast<EnemyStunnedState*>(m_pState.get()))
		stunState->Fall(pLastInteractedObj, isFirst, nrOfEnemiesFalling);
}

void game::EnemyComponent::Hit(dae::GameObject* pLastInteractedObj)
{
	auto state = dynamic_cast<EnemyChaseState*>(m_pState.get());
	if (state)
		state->Hit(100 * m_PointMultiplier, pLastInteractedObj);
	else if (auto stunState = dynamic_cast<EnemyStunnedState*>(m_pState.get()))
		stunState->Hit(100 * m_PointMultiplier, pLastInteractedObj);
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
