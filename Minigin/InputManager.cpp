#include "SDL_scancode.h"
#include "InputManager.h"

static int M_NROFGAMEPADSET = 0;

dae::InputManager::InputManager()
{
	m_pKeyBoard = std::make_unique<KeyBoard>();
}

bool dae::InputManager::ProcessInput(float deltaTime)
{
	if (!m_pKeyBoard->ProcessQuitGameInput())
		return false;

	// process gamepads
	for (const auto& gamePad : m_pGamePads)
	{
		gamePad->Update(deltaTime);
		for (const auto& command : m_pGamePadCommands)
		{
			if (command->gamePadID != gamePad->GetID())
				continue;

			switch (command->state)
			{
			case InputState::Pressed:
				if (gamePad->IsButtonDownThisFrame(command->button))
					command->pCommand->Execute(deltaTime);
				break;
			case InputState::Released:
				if (gamePad->IsButtonUpThisFrame(command->button))
					command->pCommand->Execute(deltaTime);
				break;
			case InputState::Held:
				if (gamePad->IsButtonHeld(command->button))
					command->pCommand->Execute(deltaTime);
				break;
			}
		}
	}

	m_pKeyBoard->Update(deltaTime);

	// process keyboard
	for (const auto& command : m_pKeyBoardCommands)
	{
		switch (command->state)
		{
		case InputState::Pressed:
			if (m_pKeyBoard->IsKeyDownThisFrame(command->key))
				command->pCommand->Execute(deltaTime);
			break;
		case InputState::Released:
			if (m_pKeyBoard->IsKeyUpThisFrame(command->key))
				command->pCommand->Execute(deltaTime);
			break;
		case InputState::Held:
			if (m_pKeyBoard->IsKeyHeld(command->key))
				command->pCommand->Execute(deltaTime);
			break;
		}
	}
	return true;
}

void dae::InputManager::BindCommand(std::unique_ptr<Command> pCommand, int controllerID, InputState state, GamePad::GamePadButton button)
{
	auto commandInfo = std::make_unique<GamePadCommandInfo>(std::move(pCommand), controllerID, state, button);
	m_pGamePadCommands.emplace_back(std::move(commandInfo));
}

void dae::InputManager::BindCommand(std::unique_ptr<Command> pCommand, InputState state, SDL_Scancode key)
{
	auto commandInfo = std::make_unique<KeyBoardCommandInfo>(std::move(pCommand), state, key);
	m_pKeyBoardCommands.emplace_back(std::move(commandInfo));
}

void dae::InputManager::AddController()
{
	if (M_NROFGAMEPADSET < m_MaxNrOfGamePad)
		m_pGamePads.emplace_back(std::make_unique<GamePad>(M_NROFGAMEPADSET++));
}