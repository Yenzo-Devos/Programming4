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
		GameModeComponent(dae::GameObject* pOwner);
		virtual ~GameModeComponent() = default;

		GameModeComponent(const GameModeComponent& other) = delete;
		GameModeComponent(GameModeComponent&& other) = delete;
		GameModeComponent& operator=(const GameModeComponent& other) = delete;
		GameModeComponent& operator=(GameModeComponent&& other) = delete;

		void Update(float deltaTime) override;
		void HandleState();

		void Broadcast(dae::GameObject* pGameObject, dae::Event event) override;
		int GetEndPoints() const { return m_FinishedPoints; }
	private:
		std::unique_ptr<GameState> m_pState{};
		int m_FinishedPoints{ 1000 };
	};
}


