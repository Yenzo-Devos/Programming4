#pragma once
#include "IngredientState.h"
#include "GameObject.h"
#include <array>

namespace game
{
	class IngredientIdleState : public IngredientState
	{
	public:
		IngredientIdleState() = default;
		~IngredientIdleState() = default;

		IngredientIdleState(const IngredientIdleState& other) = delete;
		IngredientIdleState(IngredientIdleState&& other) = delete;
		IngredientIdleState& operator=(const IngredientIdleState& other) = delete;
		IngredientIdleState& operator=(IngredientIdleState&& other) = delete;

		std::unique_ptr<IngredientState> HandleState(dae::GameObject&) override;
		void OnEnter(dae::GameObject& owner) override;

		void Hit(int index, dae::GameObject& owner, dae::GameObject* interactedObj);
	private:
		std::array<bool, 4> m_IsLowered{};
		dae::GameObject* m_pLastInteractedObj{};
	};
}


