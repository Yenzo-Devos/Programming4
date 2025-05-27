#pragma once
#include "PlayerState.h"
#include "glm.hpp"
namespace game
{
	class MoveState : public PlayerState
	{
	public:
		MoveState() = default;
		void Update(float) override;
		PlayerState* HandleInput(PlayerComponent& playerComp) override;
		void OnEnter(PlayerComponent& playerComp) override;
	private:
		glm::vec3 m_LastPos;
	};
}


