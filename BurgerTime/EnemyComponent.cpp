#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(dae::GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

void EnemyComponent::Update(float deltaTime)
{
	m_pState->Update(deltaTime);
	HandleState();
}

void EnemyComponent::HandleState()
{
	auto newState = m_pState->HandleState(*m_pOwner);
	if (newState != nullptr)
	{
		m_pState->OnExit(*m_pOwner);
		m_pState = std::move(newState);
		m_pState->OnEnter(*m_pOwner);
	}
}
