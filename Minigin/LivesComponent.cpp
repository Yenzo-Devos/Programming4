#include "LivesComponent.h"

dae::LivesComponent::LivesComponent(GameObject* owner, int maxLives)
	: BaseComponent(owner)
	, Subject()
	, m_MaxLives{ maxLives }
	, m_CurrentLives{ maxLives }
{
}

void dae::LivesComponent::LoseLife(int amount)
{
	if (m_CurrentLives > 0)
	{
		m_CurrentLives -= amount;
		Broadcast(m_pOwner, dae::Event::OnPlayerDeath);
	}
}
