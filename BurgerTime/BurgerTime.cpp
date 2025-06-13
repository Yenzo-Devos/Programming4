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

void LoadSounds()
{
	//auto& sdlSoundSystem = dae::ServiceLocator::GetSoundSystem();
	//sdlSoundSystem.Load("../Data/sounds/Death.wav", "Death");
	//sdlSoundSystem.Load("../Data/sounds/Pepper_Shake.wav", "PepperShake");
	//sdlSoundSystem.Load("../Data/sounds/Round_Clear.wav", "RoundClear");
	
	//sdlSoundSystem.Load("../Data/sounds/Enemy_Fall.wav", "EnemyFall");
	//sdlSoundSystem.Load("../Data/sounds/Enemy_Sprayed.wav", "EnemySprayed");
	//sdlSoundSystem.Load("../Data/sounds/Enemy_Squashed.wav", "EnemySquashed");
	
	//sdlSoundSystem.Load("../Data/sounds/Burger_Fall.wav", "BurgerFall");
	//sdlSoundSystem.Load("../Data/sounds/Burger_Land.wav", "BurgerLand");
	//sdlSoundSystem.Load("../Data/sounds/Burger_Step.wav", "BurgerStep");
}

void load()
{
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	LoadSounds();

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

	//auto menuComp = scene->GetObjectByTag("menu")->GetComponent<game::MenuComponent>();
	//auto confirmCommand = std::make_unique<game::MenuConfirmCommand>(cursor, scene->GetObjectByTag("menu"));
	//auto menuMoveUpCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{0.f, -1.f});
	//auto menuMoveDownCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{ 0.f, 1.f });
	//
	//dae::InputManager::GetInstance().BindCommand(std::move(confirmCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::BUTTON_A);
	//dae::InputManager::GetInstance().BindCommand(std::move(menuMoveUpCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_UP);
	//dae::InputManager::GetInstance().BindCommand(std::move(menuMoveDownCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_DOWN);

	// example code
	//auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//auto& levelLoader = game::LevelLoader::GetInstance().GetInstance();
	//// creating and loading sound and soundsystem
	//dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	//levelLoader.LoadLevel("../Data/", "levels/level1.json", scene);
	//dae::CollisionHandler::GetInstance().Init();
	//
	////auto& sdlSoundSystem = dae::ServiceLocator::GetSoundSystem();
	////dae::AudioFile deathAudio{ "../Data/sounds/Death.wav", "Death", 0 };
	////dae::AudioFile coinAudio{ "../Data/sounds/Coin.wav", "Coin",  0 };
	////dae::AudioFile bonusSpawnedAudio{ "../Data/sounds/Bonus_Appear.wav", "BonusSpawned", 0 };
	////
	////sdlSoundSystem.Load("../Data/sounds/Death.wav", "Death");
	////sdlSoundSystem.Load("../Data/sounds/Coin.wav", "Coin");
	////sdlSoundSystem.Load("../Data/sounds/Bonus_Appear.wav", "BonusSpawned");
	//
	////auto textObj = scene.CreateObject();
	////textObj->SetLocalPosition(glm::vec3{ 80.f, 20.f, 0.f });
	////textObj->AddComponent<dae::RenderComponent>();
	////textObj->AddComponent<dae::TextComponent>(textObj->GetComponent<dae::RenderComponent>());
	////textObj->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	////textObj->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 36);
	////scene.Add(std::move(textObj));
	//
	//auto scoreTextObj = scene.CreateObject();
	//scoreTextObj->SetLocalPosition(glm::vec3{ 0.f, 4.f, 0.f });
	//scoreTextObj->AddComponent<dae::RenderComponent>();
	//scoreTextObj->AddComponent<dae::TextComponent>(scoreTextObj->GetComponent<dae::RenderComponent>());
	//scoreTextObj->GetComponent<dae::TextComponent>()->SetText("SCORE");
	//scoreTextObj->GetComponent<dae::TextComponent>()->SetFont("ui_objects/burger_time_font.otf", 18);
	//scene.Add(std::move(scoreTextObj));
	//
	//auto pepperTextObj = scene.CreateObject();
	//pepperTextObj->SetLocalPosition(glm::vec3{ 310.f, 4.f, 0.f});
	//pepperTextObj->AddComponent<dae::RenderComponent>();
	//pepperTextObj->AddComponent<dae::TextComponent>(pepperTextObj->GetComponent<dae::RenderComponent>());
	//pepperTextObj->GetComponent<dae::TextComponent>()->SetText("PEPPER");
	//pepperTextObj->GetComponent<dae::TextComponent>()->SetFont("ui_objects/burger_time_font.otf", 18);
	//scene.Add(std::move(pepperTextObj));
	//
	//auto pepperCountObj = scene.CreateObject();
	//pepperCountObj->SetLocalPosition(glm::vec3{ 400.f, 30.f, 0.f });
	//pepperCountObj->AddComponent<dae::RenderComponent>();
	//pepperCountObj->AddComponent<dae::TextComponent>(pepperCountObj->GetComponent<dae::RenderComponent>());
	//pepperCountObj->GetComponent<dae::TextComponent>()->SetText("5");
	//pepperCountObj->GetComponent<dae::TextComponent>()->SetFont("ui_objects/burger_time_font.otf", 18);
	//pepperCountObj->AddComponent<game::PepperDisplayComponent>(pepperCountObj->GetComponent<dae::TextComponent>());
	//
	//auto chefPointsObj = scene.CreateObject();
	//chefPointsObj->SetLocalPosition(glm::vec3{ 4.f, 24.f, 0.f });
	//chefPointsObj->AddComponent<dae::RenderComponent>();
	//chefPointsObj->AddComponent<dae::TextComponent>(chefPointsObj->GetComponent<dae::RenderComponent>());
	//chefPointsObj->GetComponent<dae::TextComponent>()->SetText("0");
	//chefPointsObj->GetComponent<dae::TextComponent>()->SetFont("ui_objects/burger_time_font.otf", 18);
	//chefPointsObj->AddComponent<game::PointsDisplayComponent>(chefPointsObj->GetComponent<dae::TextComponent>());
	//
	//auto chefLivesObj = scene.CreateObject();
	//chefLivesObj->SetLocalPosition(glm::vec3{ 0.f, 480.f, 0.f });
	//chefLivesObj->AddComponent<dae::RenderComponent>(true);
	//chefLivesObj->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{ 0, 464, 16, 16 }, dae::RenderComponent::Rect{ 0, 0, 16, 16 }, 0, -16);
	//chefLivesObj->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{ 0, 448, 16, 16 }, dae::RenderComponent::Rect{ 0, 0, 16, 16 }, 0, -32);
	//chefLivesObj->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{ 0, 432, 16, 16 }, dae::RenderComponent::Rect{ 0, 0, 16, 16 }, 0, -48);
	//chefLivesObj->AddComponent<dae::TextureComponent>(chefLivesObj->GetComponent<dae::RenderComponent>());
	//chefLivesObj->GetComponent<dae::TextureComponent>()->LoadTexture("ui_objects/life_texture.png");
	//chefLivesObj->AddComponent<game::LivesDisplayComponent>(chefLivesObj->GetComponent<dae::TextureComponent>());
	//
	//auto chefObj = scene.GetObjectByTag("player0");
	//auto pepperObj = scene.GetObjectByTag("pepper");
	//pepperObj->GetComponent<game::PepperComponent>()->AddObserver(pepperCountObj->GetComponent<game::PepperDisplayComponent>());
	//chefObj->GetComponent<game::LivesComponent>()->AddObserver(chefLivesObj->GetComponent<game::LivesDisplayComponent>());
	//chefObj->GetComponent<game::PointsComponent>()->AddObserver(chefPointsObj->GetComponent<game::PointsDisplayComponent>());
	//scene.Add(std::move(pepperCountObj));
	//scene.Add(std::move(chefLivesObj));
	//scene.Add(std::move(chefPointsObj));
	//
	//// enemy objects
	////auto pepperObj = scene.CreateObject();
	////pepperObj->SetLocalPosition(glm::vec3{ 120.f, 120.f, 0.f });
	////pepperObj->AddComponent<dae::RenderComponent>(true);
	////pepperObj->AddComponent<dae::SpriteComponent>(pepperObj->GetComponent<dae::RenderComponent>(), 16, 16);
	////pepperObj->GetComponent<dae::SpriteComponent>()->LoadTexture("hotdog_sprite_sheet.png");
	////pepperObj->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkLeft", 2, 1, 1.f);
	////pepperObj->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkRight", 2, 2, 1.f);
	////pepperObj->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkUp", 2, 3, 1.f);
	////pepperObj->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkDown", 2, 4, 1.f);
	////pepperObj->GetComponent<dae::SpriteComponent>()->LoadAnimationData("dying", 4, 5, 1.f);
	////pepperObj->GetComponent<dae::SpriteComponent>()->LoadAnimationData("sprayed", 2, 6, 1.f);
	////pepperObj->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("walkLeft");
	////pepperObj->AddComponent<game::LivesComponent>(3);
	//
	//auto enemyObj = scene.GetObjectByTag("enemy");
	////auto pepperLivesObj = scene.CreateObject();
	////pepperLivesObj->SetLocalPosition(glm::vec3{ 20.f, 140.f, 0.f });
	////pepperLivesObj->AddComponent<dae::RenderComponent>();
	////pepperLivesObj->AddComponent<dae::TextComponent>(pepperLivesObj->GetComponent<dae::RenderComponent>());
	////pepperLivesObj->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 12);
	////pepperLivesObj->AddComponent<game::LivesDisplayComponent>(pepperLivesObj->GetComponent<dae::TextComponent>());
	////pepperObj->GetComponent<game::LivesComponent>()->AddObserver(pepperLivesObj->GetComponent<game::LivesDisplayComponent>());
	////scene.Add(std::move(pepperLivesObj));
	//
	//// adding controllers
	//dae::InputManager::GetInstance().AddController();
	//
	//float speed = 100.f;
	//auto moveLeftCommand = std::make_unique<game::MoveCommand>(chefObj, speed, glm::vec3(-1, 0, 0));
	//auto moveRightCommand = std::make_unique<game::MoveCommand>(chefObj, speed, glm::vec3(1, 0, 0));
	//auto moveUpCommand = std::make_unique<game::MoveCommand>(chefObj, speed, glm::vec3(0, -1, 0));
	//auto moveDownCommand = std::make_unique<game::MoveCommand>(chefObj, speed, glm::vec3(0, 1, 0));
	//auto ThrowPepperCommand = std::make_unique<game::ThrowPepperCommand>(chefObj);
	//
	//dae::InputManager::GetInstance().BindCommand(std::move(moveLeftCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_LEFT);
	//dae::InputManager::GetInstance().BindCommand(std::move(moveRightCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_RIGHT);
	//dae::InputManager::GetInstance().BindCommand(std::move(moveUpCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_UP);
	//dae::InputManager::GetInstance().BindCommand(std::move(moveDownCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_DOWN);
	//dae::InputManager::GetInstance().BindCommand(std::move(ThrowPepperCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::BUTTON_B);
	//
	//// adding keyboard movement
	//auto moveLeftCommandKeyBoard = std::make_unique<game::MoveCommand>(enemyObj, speed, glm::vec3(-1, 0, 0));
	//auto moveRightCommandKeyBoard = std::make_unique<game::MoveCommand>(enemyObj, speed, glm::vec3(1, 0, 0));
	//auto moveUpCommandKeyBoard = std::make_unique<game::MoveCommand>(enemyObj, speed, glm::vec3(0, -1, 0));
	//auto moveDownCommandKeyBoard = std::make_unique<game::MoveCommand>(enemyObj, speed, glm::vec3(0, 1, 0));
	//
	//dae::InputManager::GetInstance().BindCommand(std::move(moveLeftCommandKeyBoard), dae::InputState::Held, SDL_SCANCODE_A);
	//dae::InputManager::GetInstance().BindCommand(std::move(moveRightCommandKeyBoard), dae::InputState::Held, SDL_SCANCODE_D);
	//dae::InputManager::GetInstance().BindCommand(std::move(moveUpCommandKeyBoard), dae::InputState::Held, SDL_SCANCODE_W);
	//dae::InputManager::GetInstance().BindCommand(std::move(moveDownCommandKeyBoard), dae::InputState::Held, SDL_SCANCODE_S);
}	
	
int main(int, char* [])
{
    dae::Minigin engine("../Data/");
    engine.Run(load);
    return 0;
}