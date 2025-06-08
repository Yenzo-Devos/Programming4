#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "IngredientState.h"
#include <array>

namespace game
{
	class IngredientComponent : public dae::BaseComponent
	{
	public:
		IngredientComponent(dae::GameObject* pOwner);
		~IngredientComponent() = default;

		IngredientComponent(const IngredientComponent& other) = delete;
		IngredientComponent(IngredientComponent&& other) = delete;
		IngredientComponent& operator=(const IngredientComponent& other) = delete;
		IngredientComponent& operator=(IngredientComponent&& other) = delete;

		void Update(float elapsedSec) override;
		void HandleState();

		void Drop();
		void Hit(int index);

	private:
		std::unique_ptr<game::IngredientState> m_pState;
		std::array<bool, 4> m_IsLowered{};
	};
}