#pragma once
#include "Command.h"

namespace dae
{
	class GameObject;
}

namespace game 
{
	class MoveCommand : public dae::GameObjectCommand
	{
	public:
		MoveCommand(dae::GameObject* pGameObject, float speed, glm::vec3 direction);
		~MoveCommand() = default;

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;
		void Execute(float deltaTime) override;

	private:
		float m_Speed;
		glm::vec3 m_Direction;
	};

	class KillCommand : public dae::GameObjectCommand
	{
	public:
		KillCommand(dae::GameObject* pGameObject);
		~KillCommand() = default;

		KillCommand(const KillCommand& other) = delete;
		KillCommand(KillCommand&& other) = delete;
		KillCommand& operator=(const KillCommand& other) = delete;
		KillCommand& operator=(KillCommand&& other) = delete;
		void Execute(float) override;
	};
}