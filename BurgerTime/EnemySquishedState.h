#pragma once
#include "EnemyState.h"

namespace game
{
	class EnemySquishedState : public EnemyState
	{
	public:
		EnemySquishedState() = default;
		EnemySquishedState(int pointsToBeAwarded, dae::GameObject* pLastInteractedObj);
		void Update(float deltaTime) override;
		std::unique_ptr<EnemyState> HandleState(dae::GameObject&) override;
		void OnEnter(dae::GameObject& owner) override;
		//virtual void OnExit(dae::GameObject&) {}
	
	private:
		float m_AccuAnimTime{ 0.f };
		const float m_AnimTime{ 1.f };
		int m_PointsToBeAwarded{};
		dae::GameObject* m_pLastInteractedObj{};
	};
}