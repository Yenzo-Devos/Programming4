#include "LivesComponent.h"

game::LivesComponent::LivesComponent(dae::GameObject* owner, int maxLives)
	: BaseComponent(owner)
	, m_MaxLives{ maxLives }
	, m_CurrentLives{ maxLives }
{
}

void game::LivesComponent::LoseLife(int amount)
{
	if (m_CurrentLives > 0)
	{
		m_CurrentLives -= amount;
		m_pPlayerDiedEvent->Broadcast(m_pOwner, dae::Event::OnPlayerDeath);
	}
}

void game::LivesComponent::AddObserver(dae::Observer* pObserver)
{
	m_pPlayerDiedEvent->AddObserver(pObserver);
}

void game::LivesComponent::RemoveObserver(dae::Observer* pObserver)
{
	m_pPlayerDiedEvent->RemoveObserver(pObserver);
}
