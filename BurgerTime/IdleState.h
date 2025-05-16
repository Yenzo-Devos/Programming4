#pragma once
#include "PlayerState.h"
#include "PlayerComponent.h"
#include "glm.hpp"

namespace game
{
	class IdleState : public PlayerState
	{
	public:
		IdleState() = default;
		void Update(float) override;
		PlayerState* HandleInput(PlayerComponent& playerComp) override;
		void OnEnter(PlayerComponent& playerComp) override;
		//void OnExit(PlayerComponent* playerComp) override {};
	private:
		glm::vec3 m_LastPos;
	};
}


