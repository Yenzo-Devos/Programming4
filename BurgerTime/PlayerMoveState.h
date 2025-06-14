#pragma once
#include "PlayerState.h"
#include "glm.hpp"
namespace game
{
	class PlayerMoveState : public PlayerState
	{
	public:
		PlayerMoveState() = default;
		~PlayerMoveState() = default;

		PlayerMoveState(const PlayerMoveState& other) = delete;
		PlayerMoveState(PlayerMoveState&& other) = delete;
		PlayerMoveState& operator=(const PlayerMoveState& other) = delete;
		PlayerMoveState& operator=(PlayerMoveState&& other) = delete;

		std::unique_ptr<PlayerState> HandleState(dae::GameObject* pOwner) override;
		void OnEnter(dae::GameObject* pOwner) override;

		void ChangeDirection(glm::vec2 direction);
		void Throw();
	private:
		glm::vec2 m_LastPos{};
		glm::vec2 m_Direction{};
		bool m_Throw{ false };
		int m_CurrentHealth{};
	};
}


