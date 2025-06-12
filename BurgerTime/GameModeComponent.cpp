#include "GameModeComponent.h"
#include "StartScreenState.h"
#include "GameObject.h"
#include "CursorComponent.h"
#include "MenuComponent.h"

game::GameModeComponent::GameModeComponent(dae::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_pState{ std::make_unique<StartScreenState>() }
{
}

void game::GameModeComponent::Update(float deltaTime)
{
	m_pState->Update(deltaTime);
	HandleState();
}

void game::GameModeComponent::HandleState()
{
	auto newState = m_pState->HandleState(*m_pOwner);
	if (newState != nullptr)
	{
		m_pState->OnExit(*m_pOwner);
		m_pState = std::move(newState);
		m_pState->OnEnter(*m_pOwner);
	}
}

void game::GameModeComponent::Broadcast(dae::GameObject* pGameObject, dae::Event event)
{
	switch (event)
	{
	case dae::Event::OnCursorClicked:
	{
		auto state = dynamic_cast<StartScreenState*>(m_pState.get());
		if (state)
			state->ModeSelected(pGameObject->GetComponent<MenuComponent>()->GetItemSelected());
		break;
	}
	default:
		break;
	}
}
