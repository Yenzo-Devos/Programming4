#pragma once
#include "EnemyState.h"

namespace game
{
	class EnemySquishedState : public EnemyState
	{
	public:
		EnemySquishedState() = default;
		EnemySquishedState(int pointsToBeAwarded, dae::GameObject* pLastInteractedObj);
		~EnemySquishedState() = default;

		EnemySquishedState(const EnemySquishedState& other) = delete;
		EnemySquishedState(EnemySquishedState&& other) = delete;
		EnemySquishedState& operator=(const EnemySquishedState& other) = delete;
		EnemySquishedState& operator=(EnemySquishedState&& other) = delete;

		void Update(float deltaTime) override;
		std::unique_ptr<EnemyState> HandleState(dae::GameObject&) override;
		void OnEnter(dae::GameObject& owner) override;
	
	private:
		float m_AccuAnimTime{ 0.f };
		const float m_AnimTime{ 1.f };
		int m_PointsToBeAwarded{};
		dae::GameObject* m_pLastInteractedObj{};
	};
}