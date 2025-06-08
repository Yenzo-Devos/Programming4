#pragma once
#include "PlayerState.h"
#include "glm.hpp"
namespace game
{
	class PlayerMoveState : public PlayerState
	{
	public:
		PlayerMoveState() = default;
		void Update(float) override {};
		std::unique_ptr<PlayerState> HandleState(PlayerComponent& playerComp) override;
		void OnEnter(PlayerComponent& playerComp) override;
		void ChangeDirection(glm::vec3 direction);
	private:
		glm::vec3 m_LastPos{};
		glm::vec3 m_Direction{};
	};
}


