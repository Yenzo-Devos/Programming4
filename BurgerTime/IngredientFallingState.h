#pragma once
#include "IngredientState.h"
#include "HitboxComponent.h"
#include <unordered_set>

namespace game
{
	class IngredientFallingState : public IngredientState
	{
	public:
		IngredientFallingState() = default;
		IngredientFallingState(dae::GameObject* pLastInteractedObj);
		~IngredientFallingState() = default;

		IngredientFallingState(const IngredientFallingState& other) = delete;
		IngredientFallingState(IngredientFallingState&& other) = delete;
		IngredientFallingState& operator=(const IngredientFallingState& other) = delete;
		IngredientFallingState& operator=(IngredientFallingState&& other) = delete;

		virtual void Update(float deltaTime);
		virtual std::unique_ptr<IngredientState> HandleState(dae::GameObject&);
		virtual void OnEnter(dae::GameObject& owner);
		virtual void OnExit(dae::GameObject& owner);
	
	private:
		const float m_GraceTime{ 0.25f };
		float m_AccuGraceTimer{ 0.f };
		bool m_GracePeriodOver{ false };

		dae::GameObject* m_pLastInteractedObj{};
		dae::HitboxComponent* m_pHitboxComp{};
		void EmptyLandingPlatform();
		std::unordered_set<dae::GameObject*> CheckIfEnemiesCollide();
	};
}


