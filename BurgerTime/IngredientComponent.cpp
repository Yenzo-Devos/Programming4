#include "IngredientComponent.h"
#include "IngredientIdleState.h"
#include "IngredientFallingState.h"
#include "RenderComponent.h"
#include "FallComponent.h"
#include <algorithm>

game::IngredientComponent::IngredientComponent(dae::GameObject* pOwner, int type)
	: BaseComponent(pOwner)
	, m_Type{type}
	, m_pState{ std::make_unique<IngredientIdleState>() }
	, m_pIngredientFellOnPlateEvent{ std::make_unique<dae::Subject>() }
{
}

void game::IngredientComponent::Update(float deltaTime)
{
	m_pState->Update(deltaTime);
	HandleState();
}

void game::IngredientComponent::HandleState()
{
	auto newState = m_pState->HandleState(*m_pOwner);
	if (newState != nullptr)
	{
		m_pState->OnExit(*m_pOwner);
		m_pState = std::move(newState);
		m_pState->OnEnter(*m_pOwner);
	}
}

void game::IngredientComponent::Hit(int index, dae::GameObject* pHitter)
{
	auto state = dynamic_cast<IngredientIdleState*>(m_pState.get());
	if (state)
		state->Hit(index, *m_pOwner, pHitter);
}

void game::IngredientComponent::AddObserver(dae::Observer* pObserver)
{
	m_pIngredientFellOnPlateEvent->AddObserver(pObserver);
}

void game::IngredientComponent::RemoveObserver(dae::Observer* pObserver)
{
	m_pIngredientFellOnPlateEvent->AddObserver(pObserver);
}

void game::IngredientComponent::FellOnPlate()
{
	// check type to check for ending of game
	m_pIngredientFellOnPlateEvent->Broadcast(m_pOwner, dae::Event::OnIngredientFallOnPlate);
}
