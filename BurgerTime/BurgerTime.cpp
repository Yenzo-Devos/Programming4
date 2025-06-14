#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include <glm.hpp>

#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Command.h"
#include "GameCommand.h"
#include "MenuCommands.h"

#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SDLSoundSystem.h"
#include "LevelLoader.h"
#include "CollisionHandler.h"
#include "UILoader.h"

// component includes
#include "TextComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "FPSComponent.h"
#include "LivesComponent.h"
#include "LivesDisplayComponent.h"
#include "RenderComponent.h"
#include "PointsComponent.h"
#include "PointsDisplayComponent.h"
#include "PepperComponent.h"
#include "PepperDisplayComponent.h"
//#include "RotatingComponent.h"
//#include "TrashTheCacheComponent.h"

#include "GameModeComponent.h"
#include "MenuComponent.h"
#include "CursorComponent.h"
#include "CommandLoader.h"

#include <iostream>

void load()
{
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());

	auto scene = dae::SceneManager::GetInstance().CreateScene("start_screen");
	// create the gamemode
	auto gameMode = scene->CreateObject();
	gameMode->GiveTag("gamemode");
	gameMode->AddComponent<game::GameModeComponent>();
	game::UILoader::GetInstance().LoadStartScreenUI(scene);

	auto cursor = scene->GetObjectByTag(">");
	cursor->GetComponent<game::CursorComponent>()->AddObserver(gameMode->GetComponent<game::GameModeComponent>());
	dae::SceneManager::GetInstance().SetGameMode(std::move(gameMode));

	dae::InputManager::GetInstance().AddController();
	dae::InputManager::GetInstance().AddController();
	game::CommandLoader::GetInstance().CreateStartMenuCommands(scene);

}	
	
int main(int, char* [])
{
    dae::Minigin engine("../Data/");
    engine.Run(load);
    return 0;
}