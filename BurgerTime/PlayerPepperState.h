#pragma once
#include "PlayerState.h"
#include "glm.hpp"

namespace game
{
	class PlayerPepperState : public PlayerState
	{
	public:
		PlayerPepperState() = default;
		void Update(float deltaTime) override;
		std::unique_ptr<PlayerState> HandleState(PlayerComponent&) override;
		void OnEnter(PlayerComponent& playerComp) override;
		void ChangeDirection(glm::vec3 direction);
	private:
		glm::vec3 m_Direction{};
		
		bool m_TimerDone{ false };
		float m_AccuTime{ 0.f };
		const float m_MaxPepperTime{ 1.f };
	};
}