#include "IngredientFallingState.h"

std::unique_ptr<game::IngredientState> game::IngredientFallingState::HandleState(IngredientComponent&)
{
    // if it collides with a new platform then go to Idle
    // if it collides with a plate then go to OnPlate
    // return std::unique_ptr<IngredientState>();
    return nullptr;
}
