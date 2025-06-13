#pragma once
#include "PlayerState.h"
#include "glm.hpp"

namespace game
{
	class PlayerDyingState : public PlayerState
	{
	public:
		PlayerDyingState() = default;
		~PlayerDyingState() = default;

		PlayerDyingState(const PlayerDyingState& other) = delete;
		PlayerDyingState(PlayerDyingState&& other) = delete;
		PlayerDyingState& operator=(const PlayerDyingState& other) = delete;
		PlayerDyingState& operator=(PlayerDyingState&& other) = delete;

		void Update(float deltaTime) override;
		std::unique_ptr<PlayerState> HandleState(dae::GameObject*) override;
		void OnEnter(dae::GameObject* owner) override;
		void OnExit(dae::GameObject* owner) override;
	private:
		glm::vec3 m_LastPos{};
		float m_AccuDeadTime{};
		const float m_DeadTime{ 2.f };
	};
}