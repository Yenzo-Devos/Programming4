#pragma once
#include "IngredientState.h"
namespace game
{
	class IngredientFallingState : public IngredientState
	{
	public:
		IngredientFallingState() = default;
		virtual void Update(float deltaTime);
		virtual std::unique_ptr<IngredientState> HandleState(dae::GameObject&);
		virtual void OnEnter(dae::GameObject& owner);
		virtual void OnExit(dae::GameObject& owner);
	
	private:
		const float m_FallingSpeed{ 10.f };
		const float m_GraceTime{ 2.f };
		float m_AccuGraceTimer{ 0.f };
		bool m_GracePeriodOver{ false };
	};
}


