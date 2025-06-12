#include "PointsComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"

game::PointsComponent::PointsComponent(dae::GameObject* owner, int currentPoints)
	: BaseComponent(owner)
	, m_pPointsScored{ std::make_unique<dae::Subject>() }
	, m_Points{ currentPoints }
{
}

void game::PointsComponent::AddObserver(dae::Observer* pObserver)
{
	m_pPointsScored->AddObserver(pObserver);
}

void game::PointsComponent::RemoveObserver(dae::Observer* pObserver)
{
	m_pPointsScored->RemoveObserver(pObserver);
}

void game::PointsComponent::AddPoints(int amount)
{
	if (m_pOwner->GetTag() == "player1")
	{
		auto player = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByTag("player0");
		player->GetComponent<PointsComponent>()->AddPoints(amount);
		return;
	}
	m_Points += amount;
	m_pPointsScored->Broadcast(m_pOwner, dae::Event::OnPlayerScored);
}