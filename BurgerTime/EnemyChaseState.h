#pragma once
#include "EnemyState.h"

namespace game
{
	class EnemyChaseState : public EnemyState
	{
	public:
		EnemyChaseState() = default;
		//virtual void Update(float) {}
		std::unique_ptr<EnemyState> HandleState(dae::GameObject&) override;
		//void OnEnter(dae::GameObject& owner) override;
		//virtual void OnExit(dae::GameObject&) {}
		void Stun() { m_IsStunned = true; }

	private:
		bool m_IsStunned{ false };
	};
}