#include "LivesComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"

game::LivesComponent::LivesComponent(dae::GameObject* owner, int maxLives)
	: BaseComponent(owner)
	, m_MaxLives{ maxLives }
	, m_CurrentLives{ maxLives }
	, m_pPlayerDiedEvent{ std::make_unique<dae::Subject>() }
{
}

void game::LivesComponent::LoseLife(int amount)
{
	if (m_CurrentLives > 0)
	{
		if (m_pOwner->GetTag() == "player1")
		{
			auto player = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByTag("player0");
			player->GetComponent<LivesComponent>()->LoseLife(1);
		}
		m_CurrentLives -= amount;
		m_pPlayerDiedEvent->Broadcast(m_pOwner, dae::Event::OnPlayerDeath);
	}
	else if (m_CurrentLives == 0)
		m_pPlayerDiedEvent->Broadcast(m_pOwner, dae::Event::OnGameEnded);
}

void game::LivesComponent::AddObserver(dae::Observer* pObserver)
{
	m_pPlayerDiedEvent->AddObserver(pObserver);
}

void game::LivesComponent::RemoveObserver(dae::Observer* pObserver)
{
	m_pPlayerDiedEvent->RemoveObserver(pObserver);
}
