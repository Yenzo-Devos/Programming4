#pragma once
#include "GameState.h"

namespace game
{
	class LeaderboardState : public GameState
	{
	public:
		LeaderboardState() = default;
		//virtual void Update(float deltaTime);
		std::unique_ptr<GameState> HandleState(dae::GameObject&) override { return nullptr; }
		void OnEnter(dae::GameObject& owner) override;
		//virtual void OnExit(dae::GameObject&) {}
	};
}