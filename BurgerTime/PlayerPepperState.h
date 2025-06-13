#pragma once
#include "PlayerState.h"
#include "glm.hpp"

namespace game
{
	class PlayerPepperState : public PlayerState
	{
	public:
		PlayerPepperState() = default;
		~PlayerPepperState() = default;

		PlayerPepperState(const PlayerPepperState& other) = delete;
		PlayerPepperState(PlayerPepperState&& other) = delete;
		PlayerPepperState& operator=(const PlayerPepperState& other) = delete;
		PlayerPepperState& operator=(PlayerPepperState&& other) = delete;

		void Update(float deltaTime) override;
		std::unique_ptr<PlayerState> HandleState(dae::GameObject* pOwner) override;
		void OnEnter(dae::GameObject* pOwner) override;
	private:
		
		bool m_TimerDone{ false };
		float m_AccuTime{ 0.f };
		const float m_MaxPepperTime{ 0.5f };
	};
}