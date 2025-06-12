#pragma once
#include "PlayerState.h"
#include "PlayerComponent.h"
#include "glm.hpp"

namespace game
{
	class PlayerDyingState : public PlayerState
	{
	public:
		PlayerDyingState() = default;
		void Update(float deltaTime) override;
		std::unique_ptr<PlayerState> HandleState(PlayerComponent&) override;
		void OnEnter(PlayerComponent& playerComp) override;
		void OnExit(PlayerComponent& playerComp) override;
	private:
		glm::vec3 m_LastPos{};
		float m_AccuDeadTime{};
		const float m_DeadTime{ 2.f };
	};
}