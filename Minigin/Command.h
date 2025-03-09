#pragma once
#include "GameObject.h"
#include "glm.hpp"
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(float) = 0;
	protected:
		Command() = default;
	};

	// create derived command for get an owned object by a controller
	class GameObjectCommand : public Command
	{
	protected:
		GameObjectCommand(GameObject* pGameObject);
		GameObject* GetGameObject() const { return m_pGameObject; }
	private:
		GameObject* m_pGameObject;
	};

	class MoveCommand : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* pGameObject, float speed, glm::vec3 direction);
		void Execute(float deltaTime) override;
	private:
		float m_Speed;
		glm::vec3 m_Direction;
	};
}

