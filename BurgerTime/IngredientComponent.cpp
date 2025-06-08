#include "IngredientComponent.h"
#include "IngredientIdleState.h"
#include "IngredientFallingState.h"
#include "RenderComponent.h"
#include "FallComponent.h"
#include <algorithm>

game::IngredientComponent::IngredientComponent(dae::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_pState{ std::make_unique<IngredientIdleState>() }
{
}

void game::IngredientComponent::Update(float elapsedSec)
{
	m_pState->Update(elapsedSec);
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

void game::IngredientComponent::Hit(int index)
{
	auto state = dynamic_cast<IngredientIdleState*>(m_pState.get());
	if (state)
		state->Hit(index, *m_pOwner);
}
