#pragma once
#include "GameState.h"
#include "GameModeComponent.h"
#include "Scene.h"

namespace game
{
	class CoopGameState : public GameState
	{
	public:
		CoopGameState() = default;
		//virtual void Update(float deltaTime);
		std::unique_ptr<GameState> HandleState(dae::GameObject*) override;
		void OnEnter(dae::GameObject* owner) override;
		void OnExit(dae::GameObject*) override;

		void EndGame() { m_GameHasEnded = true; }
		void LoadNextLevel(dae::GameObject* owner);

	private:
		int m_Level{ 1 };
		bool m_GameHasEnded{ false };

		GameModeComponent::PlayerData CreateBufferPlayerData(dae::Scene* pScene);
		void RemoveAllObjects();
	};
}