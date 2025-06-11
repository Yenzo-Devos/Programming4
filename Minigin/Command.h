#pragma once
#include "glm.hpp"
namespace dae
{
	class GameObject;
	class Command
	{
	public:
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual bool Execute(float) = 0;
	
	protected:
		Command() = default;
	};

	class GameObjectCommand : public Command
	{
	public:
		virtual ~GameObjectCommand() = default;
		GameObjectCommand(const GameObjectCommand& other) = delete;
		GameObjectCommand(GameObjectCommand&& other) = delete;
		GameObjectCommand& operator=(const GameObjectCommand& other) = delete;
		GameObjectCommand& operator=(GameObjectCommand&& other) = delete;
	
	protected:
		GameObjectCommand(GameObject* pGameObject);
		GameObject* GetGameObject() const { return m_pGameObject; }
	
	private:
		GameObject* m_pGameObject;
	};
}

