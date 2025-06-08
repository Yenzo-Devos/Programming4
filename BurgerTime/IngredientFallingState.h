#pragma once
#include "IngredientState.h"
namespace game
{
	class IngredientFallingState : public IngredientState
	{
	public:
		IngredientFallingState() = default;
		virtual void Update(float) {}
		virtual std::unique_ptr<IngredientState> HandleState(IngredientComponent&);
		virtual void OnEnter(IngredientComponent&) {}
		virtual void OnExit(IngredientComponent&) {}
	};
}


