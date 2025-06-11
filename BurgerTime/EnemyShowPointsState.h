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
		virtual void Update(float deltaTime);
		std::unique_ptr<EnemyState> HandleState(dae::GameObject&) override;
		void OnEnter(dae::GameObject& owner) override;
		void OnExit(dae::GameObject& owner) override;

	private:
		float m_AccuShowTime{ 0.f };
		const float m_ShowPointsTime{ 2.f };
		int m_PointsToBeAwarded{};
		dae::GameObject* m_pLastInteractedObj{};
		glm::vec3 m_BufferPos{};
	};
}