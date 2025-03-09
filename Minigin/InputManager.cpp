#include <SDL.h>
#include "InputManager.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"

static int M_NROFGAMEPADSET = 0;

bool dae::InputManager::ProcessInput(float deltaTime)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	//	if (e.type == SDL_KEYDOWN) {
	//		
	//	}
	//	if (e.type == SDL_MOUSEBUTTONDOWN) {
	//		
	//	}
	//	// process event for IMGUI
	//	ImGui_ImplSDL2_ProcessEvent(&e);
	}
	for (const auto& gamePad : m_pGamePads)
	{
		gamePad->Update(deltaTime);
		for (const auto& command : m_pCommands)
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
	return true;
}

void dae::InputManager::BindCommand(std::unique_ptr<Command> pCommand, int controllerID, InputState state, GamePad::GamePadButton button)
{
	std::unique_ptr<CommandInfo> commandInfo = std::make_unique<CommandInfo>(std::move(pCommand), controllerID, state, button);
	m_pCommands.emplace_back(std::move(commandInfo));
}

void dae::InputManager::AddController()
{
	if (M_NROFGAMEPADSET < m_MaxNrOfGamePad)
		m_pGamePads.emplace_back(std::make_unique<GamePad>(M_NROFGAMEPADSET++));
}
