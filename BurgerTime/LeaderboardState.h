#pragma once
#include "GameState.h"
#include "Scene.h"

namespace game
{
	class LeaderboardState : public GameState
	{
	public:
		LeaderboardState() = default;
		~LeaderboardState() = default;

		LeaderboardState(const LeaderboardState& other) = delete;
		LeaderboardState(LeaderboardState&& other) = delete;
		LeaderboardState& operator=(const LeaderboardState& other) = delete;
		LeaderboardState& operator=(LeaderboardState&& other) = delete;

		std::unique_ptr<GameState> HandleState(dae::GameObject*) override { return nullptr; }
		void OnEnter(dae::GameObject* owner) override;
	};
}