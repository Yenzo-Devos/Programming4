#pragma once
#include "GameState.h"
#include <glm.hpp>

namespace game
{
	class StartScreenState : public GameState
	{
	public:
		StartScreenState() = default;
		//virtual void Update(float deltaTime);
		std::unique_ptr<GameState> HandleState(dae::GameObject&) override;
		//void OnEnter(dae::GameObject& owner) override;
		void OnExit(dae::GameObject&) override;

		void ModeSelected(int itemIndex);
	private:
		bool m_ModeSelected{ false };
		int m_ItemIndex{-1};
	};
}