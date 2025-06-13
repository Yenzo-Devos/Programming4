#pragma once
#include "GameState.h"
#include <glm.hpp>

namespace game
{
	class StartScreenState : public GameState
	{
	public:
		StartScreenState() = default;
		~StartScreenState() = default;

		StartScreenState(const StartScreenState& other) = delete;
		StartScreenState(StartScreenState&& other) = delete;
		StartScreenState& operator=(const StartScreenState& other) = delete;
		StartScreenState& operator=(StartScreenState&& other) = delete;

		std::unique_ptr<GameState> HandleState(dae::GameObject*) override;
		void OnExit(dae::GameObject*) override;

		void ModeSelected(int itemIndex);
	private:
		bool m_ModeSelected{ false };
		int m_ItemIndex{-1};
	};
}