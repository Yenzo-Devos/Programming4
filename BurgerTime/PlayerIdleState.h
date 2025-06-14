#pragma once
#include "PlayerState.h"
#include "glm.hpp"

namespace game
{
	class PlayerIdleState : public PlayerState
	{
	public:
		PlayerIdleState() = default;
		~PlayerIdleState() = default;

		PlayerIdleState(const PlayerIdleState& other) = delete;
		PlayerIdleState(PlayerIdleState&& other) = delete;
		PlayerIdleState& operator=(const PlayerIdleState& other) = delete;
		PlayerIdleState& operator=(PlayerIdleState&& other) = delete;

		void Update(float) override {};
		std::unique_ptr<PlayerState> HandleState(dae::GameObject* pOwner) override;
		void OnEnter(dae::GameObject* pOwner) override;
	private:
		glm::vec2 m_LastPos{};
		int m_CurrentHealth{};
	};
}