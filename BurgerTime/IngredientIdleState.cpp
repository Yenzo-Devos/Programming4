#include "IngredientIdleState.h"
#include "IngredientFallingState.h"

std::unique_ptr<game::IngredientState> game::IngredientIdleState::HandleState(IngredientComponent&)
{
    // if all hitbox are hit start falling
    if (false)
        return std::make_unique<IngredientFallingState>();
    return nullptr;
}
