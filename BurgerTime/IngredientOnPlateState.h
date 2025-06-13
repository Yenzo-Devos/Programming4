#pragma once
#include "IngredientState.h"
namespace game
{
	class IngredientOnPlateState : public IngredientState
	{
	public:
		IngredientOnPlateState() = default;
		~IngredientOnPlateState() = default;

		IngredientOnPlateState(const IngredientOnPlateState& other) = delete;
		IngredientOnPlateState(IngredientOnPlateState&& other) = delete;
		IngredientOnPlateState& operator=(const IngredientOnPlateState& other) = delete;
		IngredientOnPlateState& operator=(IngredientOnPlateState&& other) = delete;

		void OnEnter(dae::GameObject& owner) override;
	};
}