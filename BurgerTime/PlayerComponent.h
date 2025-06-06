#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "PlayerState.h"

namespace game
{
	class PlayerComponent : public dae::BaseComponent
	{
	public:
		PlayerComponent(dae::GameObject* pOwner);
		virtual ~PlayerComponent() = default;

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Update(float elapsedSec) override;
		void HandleState();

		PlayerState* GetState() const { return m_pState; }
		void ChangeState(PlayerState* state);

		glm::vec3 GetDirection() const { return m_Direction; }
		void ChangeDiretion(glm::vec3 direction);

		dae::GameObject* GetOwner() { return m_pOwner; }
	private:
		PlayerState* m_pState{};
		glm::vec3 m_Direction{};
	};
}