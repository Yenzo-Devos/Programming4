#pragma once
#include "Command.h"
#include "MenuComponent.h"

namespace dae
{
	class GameObject;
}

namespace game
{
	class MenuMoveCommand : public dae::GameObjectCommand
	{
	public:
		MenuMoveCommand(dae::GameObject* pGameObject, MenuComponent* pMenu, glm::vec2 direction);
		~MenuMoveCommand() = default;

		MenuMoveCommand(const MenuMoveCommand& other) = delete;
		MenuMoveCommand(MenuMoveCommand&& other) = delete;
		MenuMoveCommand& operator=(const MenuMoveCommand& other) = delete;
		MenuMoveCommand& operator=(MenuMoveCommand&& other) = delete;
	
		bool Execute(float) override;
	
	private:
		MenuComponent* m_pMenu{};
		glm::vec2 m_Direction{};
	};

	class MenuConfirmCommand : public dae::GameObjectCommand
	{
	public:
		MenuConfirmCommand(dae::GameObject* pGameObject, dae::GameObject* pMenu);
		~MenuConfirmCommand() = default;

		MenuConfirmCommand(const MenuConfirmCommand& other) = delete;
		MenuConfirmCommand(MenuConfirmCommand&& other) = delete;
		MenuConfirmCommand& operator=(const MenuConfirmCommand& other) = delete;
		MenuConfirmCommand& operator=(MenuConfirmCommand&& other) = delete;

		bool Execute(float) override;

	private:
		dae::GameObject* m_pMenu{};
	};

	class ChangeLetterCommand : public dae::GameObjectCommand
	{
	public:
		ChangeLetterCommand(dae::GameObject* pGameObject, MenuComponent* pMenu, glm::vec2 direction);
		~ChangeLetterCommand() = default;

		ChangeLetterCommand(const ChangeLetterCommand& other) = delete;
		ChangeLetterCommand(ChangeLetterCommand&& other) = delete;
		ChangeLetterCommand& operator=(const ChangeLetterCommand& other) = delete;
		ChangeLetterCommand& operator=(ChangeLetterCommand&& other) = delete;

		bool Execute(float) override;

	private:
		MenuComponent* m_pMenu{};
		glm::vec2 m_Direction{};
	};
}

