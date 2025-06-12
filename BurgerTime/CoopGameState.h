#pragma once
#include "GameState.h"
namespace game
{
	class CoopGameState : public GameState
	{
	public:
		CoopGameState() = default;
		//virtual void Update(float deltaTime);
		std::unique_ptr<GameState> HandleState(dae::GameObject*) override { return nullptr; }
		//void OnEnter(dae::GameObject* owner) override;
		//virtual void OnExit(dae::GameObject*) {}
	};
}