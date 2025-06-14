#pragma once
#include "EnemyState.h"
#include "glm.hpp"

namespace game
{
	class EnemyShowPointsState : public EnemyState
	{
	public:
		EnemyShowPointsState() = default;
		EnemyShowPointsState(int pointsToBeAwarded, dae::GameObject* pLastInteractedObj);
		~EnemyShowPointsState() = default;

		EnemyShowPointsState(const EnemyShowPointsState& other) = delete;
		EnemyShowPointsState(EnemyShowPointsState&& other) = delete;
		EnemyShowPointsState& operator=(const EnemyShowPointsState& other) = delete;
		EnemyShowPointsState& operator=(EnemyShowPointsState&& other) = delete;

		virtual void Update(float deltaTime);
		std::unique_ptr<EnemyState> HandleState(dae::GameObject&) override;
		void OnEnter(dae::GameObject& owner) override;
		void OnExit(dae::GameObject& owner) override;

	private:
		float m_AccuShowTime{ 0.f };
		const float m_ShowPointsTime{ 2.f };
		int m_PointsToBeAwarded{};
		dae::GameObject* m_pLastInteractedObj{};
		glm::vec2 m_BufferPos{};
	};
}