#pragma once
#include "IngredientState.h"
namespace game
{
	class IngredientIdleState : public IngredientState
	{
		IngredientIdleState() = default;
		virtual void Update(float) {}
		virtual std::unique_ptr<IngredientState> HandleState(IngredientComponent&);
		virtual void OnEnter(IngredientComponent&) {}
		virtual void OnExit(IngredientComponent&) {}
	};
}


