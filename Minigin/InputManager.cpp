#include <SDL.h>
#include "InputManager.h"

bool dae::InputManager::ProcessInput(float deltaTime)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		for (auto& command : m_KeyboardCommands)
		{
			if (command.first == e.key.keysym.scancode)
				command.second->Execute(deltaTime);
		}
	}
	
	for (auto& controller : m_pControllers)
	{
		controller->PollInput();
		
		// if index is correct in command
		for (auto const& command : m_ConsoleCommands)
		{
			if (command.first.first.first != controller->GetIndex())
				continue;

			if (controller->ValidateInput(command.first.first.second, command.first.second))
				command.second->Execute(deltaTime);
		}
	}

	return true;
}

void dae::InputManager::AddController()
{
	if (m_ControllerCounter <= 2)
	{
		m_pControllers.push_back(std::make_unique<Controller>(m_ControllerCounter));
		++m_ControllerCounter;
	}
}

void dae::InputManager::BindAction(int controllerIndex, Controller::ControllerInput controllerinput, Controller::InputType keyState, std::unique_ptr<Command> pCommand)
{
	ControllerKey keyPair{ std::make_pair(controllerIndex, controllerinput) };
	ControllerKeyState statePair{ std::make_pair(keyPair, keyState) };
	m_ConsoleCommands.push_back(std::make_pair(statePair, std::move(pCommand)));
}

void dae::InputManager::BindAction(SDL_Scancode button, std::unique_ptr<Command> pCommand)
{
	m_KeyboardCommands.push_back(std::make_pair(button, std::move(pCommand)));
}
