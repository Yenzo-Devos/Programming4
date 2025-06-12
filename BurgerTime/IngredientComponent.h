#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "IngredientState.h"
#include "Subject.h"
#include <array>

namespace dae
{
	class Observer;
}

namespace game
{
	class IngredientComponent : public dae::BaseComponent
	{
	public:
		IngredientComponent(dae::GameObject* pOwner, int type);
		~IngredientComponent() = default;

		IngredientComponent(const IngredientComponent& other) = delete;
		IngredientComponent(IngredientComponent&& other) = delete;
		IngredientComponent& operator=(const IngredientComponent& other) = delete;
		IngredientComponent& operator=(IngredientComponent&& other) = delete;

		void Update(float deltaTime) override;
		void HandleState();

		void Hit(int index, dae::GameObject* pHitter);

		void AddObserver(dae::Observer* pObserver);
		void RemoveObserver(dae::Observer* pObserver);
		void FellOnPlate();
		bool IsTopBun() { return m_Type == 1; }

	private:
		int m_Type{};
		std::unique_ptr<game::IngredientState> m_pState;
		std::array<bool, 4> m_IsLowered{};

		std::unique_ptr<dae::Subject> m_pIngredientFellOnPlateEvent;
	};
}