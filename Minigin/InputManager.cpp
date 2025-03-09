#include <SDL.h>
#include "InputManager.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"

static int M_NROFGAMEPADSET = 0;

bool dae::InputManager::ProcessInput(float DeltaTime)
{
	//SDL_Event e;
	//while (SDL_PollEvent(&e)) {
	//	if (e.type == SDL_QUIT) {
	//		return false;
	//	}
	//	if (e.type == SDL_KEYDOWN) {
	//		
	//	}
	//	if (e.type == SDL_MOUSEBUTTONDOWN) {
	//		
	//	}
	//	// process event for IMGUI
	//	ImGui_ImplSDL2_ProcessEvent(&e);
	//}

	//return true;
}

void dae::InputManager::AddController()
{
	if (M_NROFGAMEPADSET < m_MaxNrOfGamePad)
		m_pGamePads.emplace_back(std::make_unique<GamePad>(M_NROFGAMEPADSET++));
}
