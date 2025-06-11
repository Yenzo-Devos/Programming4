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
	};
}