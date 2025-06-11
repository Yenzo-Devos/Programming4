#include "PointsComponent.h"

game::PointsComponent::PointsComponent(dae::GameObject* owner)
	: BaseComponent(owner)
	, m_pPointsScored{ std::make_unique<dae::Subject>() }
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
	m_Points += amount;
	m_pPointsScored->Broadcast(m_pOwner, dae::Event::OnPlayerScored);
}