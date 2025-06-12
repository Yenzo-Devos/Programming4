#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "PlayerState.h"

namespace game
{
	class PlayerComponent : public dae::BaseComponent
	{
	public:
		PlayerComponent(dae::GameObject* pOwner, dae::GameObject* pPepper);
		~PlayerComponent() = default;

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Update(float deltaTime) override;
		void HandleState();

		PlayerState* GetState() const { return m_pState.get(); }

		glm::vec3 GetDirection() const { return m_Direction; }
		void ChangeDirection(glm::vec3 direction);

		bool CheckIfPlayerMoved() const;

		dae::GameObject* GetOwner() { return m_pOwner; }
		dae::GameObject* GetPepper() { return m_pPepper; }
			 
		void ActivatePepper(glm::vec2 pos, glm::vec2 dir);
	private:
		dae::GameObject* m_pPepper{};
		std::unique_ptr<PlayerState> m_pState{};
		glm::vec3 m_Direction{};
		glm::vec3 m_LastPos{};
	};
}