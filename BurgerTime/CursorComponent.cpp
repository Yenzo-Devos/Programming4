#include "CursorComponent.h"

game::CursorComponent::CursorComponent(dae::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_pOnClicked{ std::make_unique<dae::Subject>() }
{
}

void game::CursorComponent::Click(dae::GameObject* menu)
{
	m_pOnClicked->Broadcast(menu, dae::Event::OnCursorClicked);
}

void game::CursorComponent::AddObserver(dae::Observer* pObserver)
{
	m_pOnClicked->AddObserver(pObserver);
}

void game::CursorComponent::RemoveObserver(dae::Observer* pObserver)
{
	m_pOnClicked->RemoveObserver(pObserver);
}
