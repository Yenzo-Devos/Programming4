#pragma once
#include "EnemyState.h"

namespace game
{
	class EnemyMovingState : public EnemyState
	{
	public:
		EnemyMovingState() = default;
		//virtual void Update(float) {}
		std::unique_ptr<EnemyState> HandleState(dae::GameObject&) override;
		//void OnEnter(dae::GameObject& owner) override;
		//virtual void OnExit(dae::GameObject&) {}
	};
}