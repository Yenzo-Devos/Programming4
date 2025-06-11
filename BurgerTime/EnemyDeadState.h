#pragma once
#include "EnemyState.h"

namespace game
{
	class EnemyDeadState : public EnemyState
	{
	public:
		EnemyDeadState() = default;
		EnemyDeadState(int pointsToBeAwarded, dae::GameObject* pLastInteractedObj);
		virtual void Update(float deltaTime);
		std::unique_ptr<EnemyState> HandleState(dae::GameObject& owner) override;
		void OnEnter(dae::GameObject& owner) override;
		//virtual void OnExit(dae::GameObject&) {}

	private:
		float m_AccuDeadTime{ 0.f };
		float m_DeadTime{ 5.f };
		int m_PointsToBeAwarded{};
		dae::GameObject* m_pLastInteractedObj{};
	};
}


