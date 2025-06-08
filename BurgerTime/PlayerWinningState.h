#pragma once
#include "PlayerState.h"
#include "PlayerComponent.h"
#include "glm.hpp"

namespace game
{
	class PlayerWinningState : public PlayerState
	{
	public:
		PlayerWinningState() = default;
		void Update(float) override {};
		std::unique_ptr<PlayerState> HandleState(PlayerComponent&) override { return nullptr; }
		void OnEnter(PlayerComponent&) override {}
		//void OnExit(PlayerComponent* playerComp) override {};
	private:
		glm::vec3 m_LastPos{};
	};
}

