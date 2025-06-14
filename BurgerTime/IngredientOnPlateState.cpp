#include "IngredientOnPlateState.h"
#include "HitboxComponent.h"
#include "IngredientComponent.h"

void game::IngredientOnPlateState::OnEnter(dae::GameObject* owner)
{
	owner->GetComponent<IngredientComponent>()->FellOnPlate();
}
