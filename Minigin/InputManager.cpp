#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

bool engine::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		for (auto& objectController : m_pObjectControllers)
		{
			objectController->ProcessKeyboardInput(e);
		}

		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	
	for (auto& objectController : m_pObjectControllers)
	{
		objectController->ProcessControllerInput();
	}
	
	return true;
}

void engine::InputManager::AddObjectController(std::unique_ptr<input::ObjectController>& objectController)
{
	m_pObjectControllers.emplace_back(std::move(objectController));
}
