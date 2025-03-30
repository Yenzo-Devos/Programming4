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

// component includes
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "LivesComponent.h"
#include "LivesDisplayComponent.h"
//#include "RotatingComponent.h"
//#include "TrashTheCacheComponent.h"

#include <iostream>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto bgObj = std::make_unique<dae::GameObject>();
	bgObj->AddComponent<dae::TextureComponent>();
	bgObj->GetComponent<dae::TextureComponent>()->LoadTexture("background.tga");
	scene.Add(std::move(bgObj));

	auto logoObj = std::make_unique<dae::GameObject>();
	logoObj->SetLocalPosition(glm::vec3{ 216.f, 180.f, 0.f });
	logoObj->AddComponent<dae::TextureComponent>();
	logoObj->GetComponent<dae::TextureComponent>()->LoadTexture("logo.tga");
	scene.Add(std::move(logoObj));

	auto textObj = std::make_unique<dae::GameObject>();
	textObj->SetLocalPosition(glm::vec3{ 80.f, 20.f, 0.f });
	textObj->AddComponent<dae::TextComponent>();
	textObj->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	textObj->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 36);
	scene.Add(std::move(textObj));

	auto fpsObj = std::make_unique<dae::GameObject>();
	fpsObj->SetLocalPosition(glm::vec3{ 10.f, 10.f, 0.f });
	fpsObj->AddComponent<dae::TextComponent>();
	fpsObj->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 24);
	fpsObj->AddComponent<dae::FPSComponent>(fpsObj->GetComponent<dae::TextComponent>());
	scene.Add(std::move(fpsObj));

	auto moveTextKeyboardObj = std::make_unique<dae::GameObject>();
	moveTextKeyboardObj->SetLocalPosition(glm::vec3{ 20.f, 80.f, 0.f });
	moveTextKeyboardObj->AddComponent<dae::TextComponent>();
	moveTextKeyboardObj->GetComponent<dae::TextComponent>()->SetText("Press WASD to move mr. pepper");
	moveTextKeyboardObj->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 12);
	scene.Add(std::move(moveTextKeyboardObj));

	auto moveTextControllerObj = std::make_unique<dae::GameObject>();
	moveTextControllerObj->SetLocalPosition(glm::vec3{ 20.f, 100.f, 0.f });
	moveTextControllerObj->AddComponent<dae::TextComponent>();
	moveTextControllerObj->GetComponent<dae::TextComponent>()->SetText("Use D-Pad to move mr.chef");
	moveTextControllerObj->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 12);
	scene.Add(std::move(moveTextControllerObj));

	// player objects
	auto chefObj = std::make_unique<dae::GameObject>();
	chefObj->SetLocalPosition(glm::vec3{ 100.f, 100.f, 0.f });
	chefObj->AddComponent<dae::TextureComponent>();
	chefObj->GetComponent<dae::TextureComponent>()->LoadTexture("chef_texture.png");
	chefObj->AddComponent<game::LivesComponent>(3);

	auto chefLivesObj = std::make_unique<dae::GameObject>();
	chefLivesObj->SetLocalPosition(glm::vec3{ 20.f, 120.f, 0.f });
	chefLivesObj->AddComponent<dae::TextComponent>();
	chefLivesObj->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 12);
	chefLivesObj->AddComponent<dae::LivesDisplayComponent>(chefLivesObj->GetComponent<dae::TextComponent>());

	chefObj->GetComponent<game::LivesComponent>()->AddObserver(chefLivesObj->GetComponent<dae::LivesDisplayComponent>());
	scene.Add(std::move(chefLivesObj));

	auto pepperObj = std::make_unique<dae::GameObject>();
	pepperObj->SetLocalPosition(glm::vec3{ 120.f, 120.f, 0.f });
	pepperObj->AddComponent<dae::TextureComponent>();
	pepperObj->GetComponent<dae::TextureComponent>()->LoadTexture("pepper_texture.png");
	pepperObj->AddComponent<game::LivesComponent>(3);

	auto pepperLivesObj = std::make_unique<dae::GameObject>();
	pepperLivesObj->SetLocalPosition(glm::vec3{ 20.f, 140.f, 0.f });
	pepperLivesObj->AddComponent<dae::TextComponent>();
	pepperLivesObj->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 12);
	pepperLivesObj->AddComponent<dae::LivesDisplayComponent>(pepperLivesObj->GetComponent<dae::TextComponent>());
	pepperObj->GetComponent<game::LivesComponent>()->AddObserver(pepperLivesObj->GetComponent<dae::LivesDisplayComponent>());
	scene.Add(std::move(pepperLivesObj));

	// adding controllers
	dae::InputManager::GetInstance().AddController();

	float speed = 100.f;
	auto moveLeftCommand = std::make_unique<game::MoveCommand>(chefObj.get(), speed, glm::vec3(-1, 0, 0));
	auto moveRightCommand = std::make_unique<game::MoveCommand>(chefObj.get(), speed, glm::vec3(1, 0, 0));
	auto moveUpCommand = std::make_unique<game::MoveCommand>(chefObj.get(), speed, glm::vec3(0, -1, 0));
	auto moveDownCommand = std::make_unique<game::MoveCommand>(chefObj.get(), speed, glm::vec3(0, 1, 0));
	auto killChefCommand = std::make_unique<game::KillCommand>(chefObj.get());

	dae::InputManager::GetInstance().BindCommand(std::move(moveLeftCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_LEFT);
	dae::InputManager::GetInstance().BindCommand(std::move(moveRightCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_RIGHT);
	dae::InputManager::GetInstance().BindCommand(std::move(moveUpCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_UP);
	dae::InputManager::GetInstance().BindCommand(std::move(moveDownCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_DOWN);
	dae::InputManager::GetInstance().BindCommand(std::move(killChefCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::BUTTON_A);

	// adding keyboard movement
	auto moveLeftCommandKeyBoard = std::make_unique<game::MoveCommand>(pepperObj.get(), speed, glm::vec3(-1, 0, 0));
	auto moveRightCommandKeyBoard = std::make_unique<game::MoveCommand>(pepperObj.get(), speed, glm::vec3(1, 0, 0));
	auto moveUpCommandKeyBoard = std::make_unique<game::MoveCommand>(pepperObj.get(), speed, glm::vec3(0, -1, 0));
	auto moveDownCommandKeyBoard = std::make_unique<game::MoveCommand>(pepperObj.get(), speed, glm::vec3(0, 1, 0));
	auto killPepperCommand = std::make_unique<game::KillCommand>(pepperObj.get());

	dae::InputManager::GetInstance().BindCommand(std::move(moveLeftCommandKeyBoard), dae::InputState::Held, SDL_SCANCODE_A);
	dae::InputManager::GetInstance().BindCommand(std::move(moveRightCommandKeyBoard), dae::InputState::Held, SDL_SCANCODE_D);
	dae::InputManager::GetInstance().BindCommand(std::move(moveUpCommandKeyBoard), dae::InputState::Held, SDL_SCANCODE_W);
	dae::InputManager::GetInstance().BindCommand(std::move(moveDownCommandKeyBoard), dae::InputState::Held, SDL_SCANCODE_S);
	dae::InputManager::GetInstance().BindCommand(std::move(killPepperCommand), dae::InputState::Released, SDL_SCANCODE_X);

	scene.Add(std::move(chefObj));
	scene.Add(std::move(pepperObj));
}

int main(int, char* [])
{
    dae::Minigin engine("../Data/");
    engine.Run(load);
    return 0;
}