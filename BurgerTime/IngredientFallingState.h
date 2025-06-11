#pragma once
#include "IngredientState.h"
#include "HitboxComponent.h"

namespace game
{
	class IngredientFallingState : public IngredientState
	{
	public:
		IngredientFallingState() = default;
		IngredientFallingState(dae::GameObject* pLastInteractedObj);
		virtual void Update(float deltaTime);
		virtual std::unique_ptr<IngredientState> HandleState(dae::GameObject&);
		virtual void OnEnter(dae::GameObject& owner);
		virtual void OnExit(dae::GameObject& owner);
	
	private:
		const float m_GraceTime{ 0.5f };
		float m_AccuGraceTimer{ 0.f };
		bool m_GracePeriodOver{ false };

		dae::GameObject* m_pLastInteractedObj{};
		dae::HitboxComponent* m_pHitboxComp{};
		void EmptyLandingPlatform();
		std::vector<dae::GameObject*> CheckIfEnemiesCollide();
	};
}


