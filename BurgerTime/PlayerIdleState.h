#pragma once
#include "PlayerState.h"
#include "PlayerComponent.h"
#include "glm.hpp"

namespace game
{
	class PlayerIdleState : public PlayerState
	{
	public:
		PlayerIdleState() = default;
		void Update(float) override {};
		std::unique_ptr<PlayerState> HandleState(PlayerComponent& playerComp) override;
		void OnEnter(PlayerComponent& playerComp) override;
		//void OnExit(PlayerComponent* playerComp) override {};
	private:
		glm::vec3 m_LastPos{};
	};
}