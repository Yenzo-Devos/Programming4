#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "TrashTheCache.h"
#include "MovementComponent.h"
#include "Action.h"
#include "Command.h"
#include "InputMapping.h"
#include "ObjectController.h"
#include "InputManager.h"

void load()
{
	auto& scene = engine::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TextureComponent>("background.tga");
	scene.Add(std::move(go));

	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TextureComponent>("logo.tga");
	go->SetLocalPosition(glm::vec3{ 216, 180, 0 });
	scene.Add(std::move(go));

	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TextComponent>("Programming 4 Assignment");
	go->SetLocalPosition(glm::vec3{ 80, 20, 0 });
	scene.Add(std::move(go));

	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TextComponent>();
	go->AddComponent<engine::FPSComponent>(go->GetComponent<engine::TextComponent>());
	scene.Add(std::move(go));

	/*auto digger = std::make_shared<engine::GameObject>();
	digger->AddComponent<engine::TextureComponent>("CDBIG1.BMP");
	digger->AddComponent<engine::RotatorComponent>(glm::vec3{ 200, 100, 0 }, 25.f, 1.f);

	auto childDigger = std::make_shared<engine::GameObject>();
	childDigger->AddComponent<engine::TextureComponent>("CDBIG1.BMP");
	childDigger->AddComponent<engine::RotatorComponent>(glm::vec3{ 0, 0, 0 }, 25.f, 3.f);
	childDigger->SetParent(digger.get(), false);*/
	
	// scene.Add(digger);
	//scene.Add(childDigger);

	// Thrash the cache UI
	// auto imGuiUI = std::make_shared<engine::GameObject>();
	// imGuiUI->AddComponent<engine::TrashTheCache>();
	// scene.Add(imGuiUI);

	// input demo
	auto digger = std::make_shared<engine::GameObject>();
	digger->AddComponent<engine::TextureComponent>("CDBIG1.BMP");
	digger->AddComponent<engine::MovementComponent>(75.f);
	digger->SetLocalPosition(glm::vec3{ 100.f, 100.f, 0.f });
	scene.Add(digger);

	auto childDigger = std::make_shared<engine::GameObject>();
	childDigger->AddComponent<engine::TextureComponent>("CDBIG1.BMP");
	childDigger->AddComponent<engine::MovementComponent>(150.f);
	childDigger->SetLocalPosition(glm::vec3{ 200.f, 100.f, 0.f });
	scene.Add(childDigger);

	auto moveUpKey{ std::make_unique<input::Action>(std::make_unique<command::MoveUp>()) };
	auto moveDownKey{ std::make_unique<input::Action>(std::make_unique<command::MoveDown>()) };
	auto moveRightKey{ std::make_unique<input::Action>(std::make_unique<command::MoveRight>()) };
	auto moveLeftKey{ std::make_unique<input::Action>(std::make_unique<command::MoveLeft>()) };

	auto keyboardInputMap{ std::make_shared<input::InputMapping>() };
	keyboardInputMap->BindActionToInput(moveUpKey, {}, { SDL_SCANCODE_W });
	keyboardInputMap->BindActionToInput(moveDownKey, {}, { SDL_SCANCODE_S });
	keyboardInputMap->BindActionToInput(moveRightKey, {}, { SDL_SCANCODE_D });
	keyboardInputMap->BindActionToInput(moveLeftKey, {}, { SDL_SCANCODE_A });

	auto gamepadMoveUp{ std::make_unique<input::Action>(std::make_unique<command::MoveUp>()) };
	auto gamepadMoveDown{ std::make_unique<input::Action>(std::make_unique<command::MoveDown>()) };
	auto gamepadMoveRight{ std::make_unique<input::Action>(std::make_unique<command::MoveRight>()) };
	auto gamepadMoveLeft{ std::make_unique<input::Action>(std::make_unique<command::MoveLeft>()) };

	auto gamepadInputMap{ std::make_shared<input::InputMapping>() };
	gamepadInputMap->BindActionToInput(gamepadMoveUp,
		{ std::make_pair(input::ControllerInput::dPadUp, input::InputType::Pressed) }, {});
	gamepadInputMap->BindActionToInput(gamepadMoveDown,
		{ std::make_pair(input::ControllerInput::dPadDown, input::InputType::Pressed) }, {});
	gamepadInputMap->BindActionToInput(gamepadMoveRight,
		{ std::make_pair(input::ControllerInput::dPadRight, input::InputType::Pressed) }, {});
	gamepadInputMap->BindActionToInput(gamepadMoveLeft,
		{ std::make_pair(input::ControllerInput::dPadLeft, input::InputType::Pressed) }, {});

	auto controller{ std::make_unique<input::ObjectController>(digger.get()) };
	controller->SetInputMapping(keyboardInputMap);

	auto gamepadController{ std::make_unique<input::ObjectController>(childDigger.get()) };
	gamepadController->SetInputMapping(gamepadInputMap);
	gamepadController->BindToController(0);

	engine::InputManager::GetInstance().AddObjectController(controller);
	engine::InputManager::GetInstance().AddObjectController(gamepadController);
}

int main(int, char*[]) {
	engine::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}