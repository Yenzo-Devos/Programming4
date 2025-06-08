#include "IngredientComponent.h"
#include "IngredientIdleState.h"
#include "RenderComponent.h"

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
	auto newState = m_pState->HandleState(*this);
	if (newState != nullptr)
	{
		m_pState->OnExit(*this);
		m_pState = std::move(newState);
		m_pState->OnEnter(*this);
	}
}

void game::IngredientComponent::Drop()
{
	
}

void game::IngredientComponent::Hit(int index)
{
	if (m_IsLowered[index] == false)
	{
		m_IsLowered[index] = true;
		m_pOwner->GetComponent<dae::RenderComponent>()->ChangeOffset(index, index*16, 2);
	}
}