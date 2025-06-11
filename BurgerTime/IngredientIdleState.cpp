#include "IngredientIdleState.h"
#include "IngredientFallingState.h"
#include "IngredientComponent.h"
#include "RenderComponent.h"
#include "FallComponent.h"
#include <algorithm>

std::unique_ptr<game::IngredientState> game::IngredientIdleState::HandleState(dae::GameObject&)
{
    // if all hitbox are hit start falling
    if (std::all_of(m_IsLowered.begin(), m_IsLowered.end(), [](bool b) {return b; }))
        return std::make_unique<IngredientFallingState>(m_pLastInteractedObj);
    return nullptr;
}

void game::IngredientIdleState::OnEnter(dae::GameObject& owner)
{
    owner.GetComponent<FallComponent>()->Activate(false);
}

void game::IngredientIdleState::Hit(int index, dae::GameObject& owner, dae::GameObject* interactedObj)
{
    if (m_IsLowered[index] == false)
    {
        m_IsLowered[index] = true;
        owner.GetComponent<dae::RenderComponent>()->ChangeOffset(index, index*16, 2);
        m_pLastInteractedObj = interactedObj;
    }
}