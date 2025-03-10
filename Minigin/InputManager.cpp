#include <SDL.h>
#include "InputManager.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"

static int M_NROFGAMEPADSET = 0;

dae::InputManager::InputManager()
{
	int keyCount;
	SDL_GetKeyboardState(&keyCount);
	m_PreviousKeyboardState.resize(keyCount, 0);
	m_CurrentKeyboardState.resize(keyCount, 0);
}

bool dae::InputManager::ProcessInput(float deltaTime)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			return false;
	}

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

	//update keyboard
	m_PreviousKeyboardState = m_CurrentKeyboardState;

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	m_CurrentKeyboardState.assign(state, state + m_CurrentKeyboardState.size());

	// process keyboard
	for (const auto& command : m_pKeyBoardCommands)
	{
		switch (command->state)
		{
		case InputState::Pressed:
			if (IsKeyDownThisFrame(command->key))
				command->pCommand->Execute(deltaTime);
			break;
		case InputState::Released:
			if (IsKeyUpThisFrame(command->key))
				command->pCommand->Execute(deltaTime);
			break;
		case InputState::Held:
			if (IsKeyHeld(command->key))
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

bool dae::InputManager::IsKeyDownThisFrame(SDL_Scancode key) const
{
	return m_CurrentKeyboardState[key] && !m_PreviousKeyboardState[key];
}

bool dae::InputManager::IsKeyUpThisFrame(SDL_Scancode key) const
{
	return !m_CurrentKeyboardState[key] && m_PreviousKeyboardState[key];
}

bool dae::InputManager::IsKeyHeld(SDL_Scancode key) const
{
	return m_CurrentKeyboardState[key];
}
