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
		
		bool Execute(float deltaTime) override;

	private:
		float m_Speed;
		glm::vec3 m_Direction;
	
		bool Climb(float deltaTime);
		bool Walk(float deltaTime);
	
	};

	class ThrowPepperCommand : public dae::GameObjectCommand
	{
	public:
		ThrowPepperCommand(dae::GameObject* pGameObject);
		~ThrowPepperCommand() = default;

		ThrowPepperCommand(const ThrowPepperCommand& other) = delete;
		ThrowPepperCommand(ThrowPepperCommand&& other) = delete;
		ThrowPepperCommand& operator=(const ThrowPepperCommand& other) = delete;
		ThrowPepperCommand& operator=(ThrowPepperCommand&& other) = delete;

		bool Execute(float) override;
	};

	class SkipLevelCommand : public dae::GameObjectCommand
	{
	public:
		SkipLevelCommand(dae::GameObject* pGameObject);
		~SkipLevelCommand() = default;

		SkipLevelCommand(const SkipLevelCommand& other) = delete;
		SkipLevelCommand(SkipLevelCommand&& other) = delete;
		SkipLevelCommand& operator=(const SkipLevelCommand& other) = delete;
		SkipLevelCommand& operator=(SkipLevelCommand&& other) = delete;

		bool Execute(float) override;
	};

	class MuteSoundCommand : public dae::Command
	{
	public:
		MuteSoundCommand() = default;
		~MuteSoundCommand() = default;

		MuteSoundCommand(const MuteSoundCommand& other) = delete;
		MuteSoundCommand(MuteSoundCommand&& other) = delete;
		MuteSoundCommand& operator=(const MuteSoundCommand& other) = delete;
		MuteSoundCommand& operator=(MuteSoundCommand&& other) = delete;

		bool Execute(float) override;
	};
}