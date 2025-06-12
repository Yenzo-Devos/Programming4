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
		//virtual void OnExit(dae::GameObject&) {}

		void ModeSelected(glm::vec3 pos);
	private:
		bool m_ModeSelected{ false };
		float m_CursorHeight{};
	};
}