#pragma once
#include "EnemyState.h"

namespace game
{
	class EnemyStunnedState : public EnemyState
	{
	public:
		EnemyStunnedState() = default;
		virtual void Update(float deltaTime);
		std::unique_ptr<EnemyState> HandleState(dae::GameObject&) override;
		void OnEnter(dae::GameObject& owner) override;
		//virtual void OnExit(dae::GameObject&) {}
		void Fall(dae::GameObject* pLastInteractedObj, bool isFirst, int nrOfEnemiesFalling);
		void Hit(int points, dae::GameObject* pLastInteractedObj);

	private:
		bool m_IsFalling{ false };
		bool m_GotHit{ false };

		bool m_FirstToFall{ false };
		int m_NrOfEnemiesFalling{};
		dae::GameObject* m_pLastInteractedObj{};
		
		int m_PointsToBeAwarded{};
		float m_AccuStunTime{ 0.f };
		float m_StunTime{ 2.f };
	};
}



