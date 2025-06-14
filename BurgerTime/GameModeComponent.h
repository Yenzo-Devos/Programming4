#pragma once
#include "BaseComponent.h"
#include "GameState.h"
#include "Observer.h"

#include <memory>

namespace game
{
	class GameModeComponent : public dae::Observer, public dae::BaseComponent
	{
	public:
		struct PlayerData
		{
			int score;
			int nrOfPepper;
			int lives;
		};

		GameModeComponent(dae::GameObject* pOwner);
		virtual ~GameModeComponent() = default;

		GameModeComponent(const GameModeComponent& other) = delete;
		GameModeComponent(GameModeComponent&& other) = delete;
		GameModeComponent& operator=(const GameModeComponent& other) = delete;
		GameModeComponent& operator=(GameModeComponent&& other) = delete;

		void Update(float deltaTime) override;
		void HandleState();

		GameState* GetState() const { return m_pState.get(); }
		
		void Broadcast(dae::GameObject* pGameObject, dae::Event event) override;
		int GetEndPoints() const { return m_FinishedPoints; }
		
		void SetPlayerData(PlayerData playerData) { m_PlayerData = playerData; }
		PlayerData GetPlayerData() { return m_PlayerData; }
	private:
		std::unique_ptr<GameState> m_pState{};
		int m_FinishedPoints{ };
		int m_NrOfBurgerDone{ };
		bool m_LevelReloaded{ false };

		float m_AccuReloadTime{ };
		const float m_ReloadTime{ 10.f };
		PlayerData m_PlayerData{ 0, 5, 3};
	};
}


