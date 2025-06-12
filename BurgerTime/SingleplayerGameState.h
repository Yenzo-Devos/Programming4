#pragma once
#include "GameState.h"
#include "Scene.h"
namespace game
{
	class SingleplayerGameState : public GameState
	{
	public:
		SingleplayerGameState() = default;
		//virtual void Update(float deltaTime);
		std::unique_ptr<GameState> HandleState(dae::GameObject&) override;
		void OnEnter(dae::GameObject& owner) override;
		void OnExit(dae::GameObject&) override;

		void LoadNextLevel();
		void EndGame() { m_GameHasEnded = true; }
	private:
		int m_Level{1};
		bool m_GameHasEnded{ false };
		void CreateCommands(dae::Scene* pScene);
	};
}


