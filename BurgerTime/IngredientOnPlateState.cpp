#include "IngredientOnPlateState.h"

std::unique_ptr<game::IngredientState> game::IngredientOnPlateState::HandleState(IngredientComponent&)
{
    // by reset go back to idle but most of the time that will mean a new object?
    return nullptr;
}
