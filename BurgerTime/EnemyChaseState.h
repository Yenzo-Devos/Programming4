#pragma once
#include "EnemyState.h"
#include "SpriteComponent.h"
#include "ChaseComponent.h"

namespace game
{
	class EnemyChaseState : public EnemyState
	{
	public:
		EnemyChaseState() = default;
		EnemyChaseState(dae::SpriteComponent* spriteComp, ChaseComponent* chaseComp);
		virtual void Update(float) override;
		std::unique_ptr<EnemyState> HandleState(dae::GameObject&) override;
		void OnEnter(dae::GameObject& owner) override;
		virtual void OnExit(dae::GameObject&) override;
		void Stun() { m_IsStunned = true; }
		void Fall(dae::GameObject* pLastInteractedObj, bool isFirst, int nrOfEnemiesFalling);
		void Hit(int pointsToBeAwarded, dae::GameObject* pLastInteractedObj);

	private:
		bool m_IsStunned{ false };
		bool m_IsFalling{ false };
		bool m_GotHit{ false };
		int m_PointsToBeAwarded{};
		glm::vec2 m_Direction{};

		bool m_FirstToFall{ false };
		int m_NrOfEnemiesFalling{};

		dae::SpriteComponent* m_pSpriteComp{};
		ChaseComponent* m_pChaseComp{};
		dae::GameObject* m_pLastInteractedObj{};

		void ChangeAnimation(glm::vec2 dir);
	};
}