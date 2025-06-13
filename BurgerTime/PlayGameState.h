#pragma once
#include "GameState.h"
#include "Scene.h"
#include "GameModeComponent.h"

namespace game
{
	class PlayGameState : public GameState
	{
	public:
		PlayGameState(int gameModeIndex);

		std::unique_ptr<GameState> HandleState(dae::GameObject*) override;
		void OnEnter(dae::GameObject* owner) override;
		void OnExit(dae::GameObject*) override;

		void LoadNextLevel(dae::GameObject* owner);
		void EndGame() { m_GameHasEnded = true; }

	private:
		int m_GameModeIndex{};
		int m_Level{ 1 };
		bool m_GameHasEnded{ false };
		std::vector<std::string> m_SceneNames{ "singleplayer", "co-op", "versus" };

		GameModeComponent::PlayerData CreateBufferPlayerData(dae::Scene* pScene);
		void RemoveAllObjects();
	};
}