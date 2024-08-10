#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute(float deltaTime) = 0;
	};

	class MoveCommand : public Command
	{
	public:
		MoveCommand(GameObject* gameObject, glm::vec3 dir, float speed);
		virtual ~MoveCommand() = default;

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

		virtual void Execute(float deltaTime) override;
	private:
		GameObject* m_pGameObject;
		glm::vec3 m_Direction;
		float m_Speed;
	};
}


