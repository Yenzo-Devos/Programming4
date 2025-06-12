#pragma once
#include "GameState.h"
namespace game
{
	class SingleplayerGameState : public GameState
	{
	public:
		SingleplayerGameState() = default;
		//virtual void Update(float deltaTime);
		std::unique_ptr<GameState> HandleState(dae::GameObject&) override;
		//void OnEnter(dae::GameObject& owner) override;
		//virtual void OnExit(dae::GameObject&) {}
	};
}


