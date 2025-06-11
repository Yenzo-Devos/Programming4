#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "GameCommand.h"

namespace game
{
	class ChaseComponent : dae::BaseComponent
	{
	public:
		ChaseComponent(dae::GameObject* pOwner, std::vector<dae::GameObject*> pLadderVec);
		~ChaseComponent() = default;

		ChaseComponent(const ChaseComponent& other) = delete;
		ChaseComponent(ChaseComponent&& other) = delete;
		ChaseComponent& operator=(const ChaseComponent& other) = delete;
		ChaseComponent& operator=(ChaseComponent&& other) = delete;

		void Update(float deltaTime) override;
		void AddObjectToChase(dae::GameObject* object);
	
	private:
		// movement vars
		bool m_IsOnLadder{ false };
		glm::vec2 m_LockedDirection{};
		std::vector<dae::GameObject*> m_pObjectToChaseVec{};
		std::vector<dae::GameObject*> m_pLadderVec{};

		bool m_IsDirectionLocked{ false };
		float m_AccuLockedDirTime{ 0.f };
		const float m_LockedDirTime{ 2.f };

		// move commands
		std::unique_ptr<MoveCommand> m_MoveLeftCommand{};
		std::unique_ptr<MoveCommand> m_MoveRightCommand{};
		std::unique_ptr<MoveCommand> m_MoveUpCommand{};
		std::unique_ptr<MoveCommand> m_MoveDownCommand{};

		// movement logic functions
		dae::GameObject* GetClosestObjectToChase();
		void CheckMoveOnLadder(dae::GameObject* pTarget, float deltaTime);
		bool CheckLadderMovement(dae::GameObject* pTarget, float deltaTime);
		void MoveOnLockedPosition(float deltaTime);
		void LockInDirection(glm::vec2 dir);
	};
}