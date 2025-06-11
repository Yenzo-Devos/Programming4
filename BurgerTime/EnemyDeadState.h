#pragma once
#include "EnemyState.h"

namespace game
{
	class EnemyDeadState : public EnemyState
	{
	public:
		EnemyDeadState() = default;
		virtual void Update(float deltaTime);
		std::unique_ptr<EnemyState> HandleState(dae::GameObject& owner) override;
		void OnEnter(dae::GameObject& owner) override;
		//virtual void OnExit(dae::GameObject&) {}

	private:
		float m_AccuDeadTime{ 0.f };
		float m_DeadTime{ 5.f };
	};
}


