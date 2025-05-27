#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "PlayerState.h"

namespace game
{
	class PlayerComponent : dae::BaseComponent
	{
	public:
		PlayerComponent(dae::GameObject* pOwner);
		virtual ~PlayerComponent() = default;

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Update(float elapsedSec) override;
		void HandleInput();

		dae::GameObject* GetOwner() { return m_pOwner; }
	private:
		PlayerState* m_pState{};
	};
}

