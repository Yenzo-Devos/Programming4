#pragma once
#include "EnemyState.h"
#include "FallComponent.h"
#include "HitboxComponent.h"

namespace game
{
	class EnemyFallState : public EnemyState
	{
	public:
		EnemyFallState() = default;
		EnemyFallState(dae::GameObject* pLastInteractedObj, bool isFirst, int nrOfEnemiesFalling);
		~EnemyFallState() = default;

		EnemyFallState(const EnemyFallState& other) = delete;
		EnemyFallState(EnemyFallState&& other) = delete;
		EnemyFallState& operator=(const EnemyFallState& other) = delete;
		EnemyFallState& operator=(EnemyFallState&& other) = delete;

		void Update(float deltaTime);
		std::unique_ptr<EnemyState> HandleState(dae::GameObject&) override;
		void OnEnter(dae::GameObject& owner) override;
		virtual void OnExit(dae::GameObject&) override;

	private:
		FallComponent* m_pFallComp{};
		dae::HitboxComponent* m_pHitboxComp{};

		const float m_GraceTime{ 0.5f };
		float m_AccuGraceTimer{ 0.f };
		bool m_GracePeriodOver{ false };


		bool m_FirstToFall{ false };
		int m_NrOfEnemiesFalling{};
		dae::GameObject* m_pLastInteractedObj{};
	};
}