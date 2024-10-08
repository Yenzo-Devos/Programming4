#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
//#include "TextObject.h"
#include <memory>

#include "Controller.h"
#include "InputManager.h"

#include "TextComponent.h"
#include "TextureComponent.h"

void load()
{
	dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& scene = dae::SceneManager::GetInstance().GetSceneByName("Demo");
	auto& input = dae::InputManager::GetInstance();

	auto go = std::make_unique<dae::GameObject>();
	//go->AddComponent<dae::TextureComponent>();
	//go->GetComponent<dae::TextureComponent>()->LoadTexture("background.tga");
	////go->SetTexture("background.tga");
	//scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->GetComponent<dae::TextureComponent>()->LoadTexture("logo.tga");
	go->SetLocalPos(glm::vec3{ 216, 180, 0 });

	auto goChild = std::make_unique<dae::GameObject>();
	goChild->AddComponent<dae::TextureComponent>();
	goChild->GetComponent<dae::TextureComponent>()->LoadTexture("logo.tga");
	goChild->SetLocalPos(glm::vec3{ 100, 100, 0 });
	goChild->SetParent(go.get());

	scene.Add(std::move(go));
	scene.Add(std::move(goChild));

	auto player1 = std::make_unique<dae::GameObject>();
	player1->AddComponent<dae::TextureComponent>();
	player1->GetComponent<dae::TextureComponent>()->LoadTexture("qbert.png");
	player1->SetLocalPos(glm::vec3{ 50, 100, 0 });

	auto player2 = std::make_unique<dae::GameObject>();
	player2->AddComponent<dae::TextureComponent>();
	player2->GetComponent<dae::TextureComponent>()->LoadTexture("qbertEnemy.png");
	player2->SetLocalPos(glm::vec3{ 100, 200, 0 });
	
	input.AddController();
	input.AddController();

	input.BindAction(0, dae::Controller::ControllerInput::DPadUp, dae::Controller::InputType::Pressed, std::make_unique<dae::MoveCommand>(player1.get(), glm::vec3{ 0, -1, 0 }, 100.f));
	input.BindAction(0, dae::Controller::ControllerInput::DPadDown, dae::Controller::InputType::Pressed, std::make_unique<dae::MoveCommand>(player1.get(), glm::vec3{ 0, 1, 0 }, 100.f));
	input.BindAction(0, dae::Controller::ControllerInput::DPadLeft, dae::Controller::InputType::Pressed, std::make_unique<dae::MoveCommand>(player1.get(), glm::vec3{ -1, 0, 0 }, 100.f));
	input.BindAction(0, dae::Controller::ControllerInput::DPadRight, dae::Controller::InputType::Pressed, std::make_unique<dae::MoveCommand>(player1.get(), glm::vec3{ 1, 0, 0 }, 100.f));
	
	input.BindAction(1, dae::Controller::ControllerInput::DPadUp, dae::Controller::InputType::Pressed, std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3{ 0, -1, 0 }, 200.f));
	input.BindAction(1, dae::Controller::ControllerInput::DPadDown, dae::Controller::InputType::Pressed, std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3{ 0, 1, 0 }, 200.f));
	input.BindAction(1, dae::Controller::ControllerInput::DPadLeft, dae::Controller::InputType::Pressed, std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3{ -1, 0, 0 }, 200.f));
	input.BindAction(1, dae::Controller::ControllerInput::DPadRight, dae::Controller::InputType::Pressed, std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3{ 1, 0, 0 }, 200.f));
	
	input.BindAction(SDL_SCANCODE_W, std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3{ 0, -1, 0 }, 200.f));
	input.BindAction(SDL_SCANCODE_S, std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3{ 0, 1, 0 }, 200.f));
	input.BindAction(SDL_SCANCODE_A, std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3{ -1, 0, 0 }, 200.f));
	input.BindAction(SDL_SCANCODE_D, std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3{ 1, 0, 0 }, 200.f));

	scene.Add(std::move(player1));
	scene.Add(std::move(player2));

	//auto to = std::make_unique<dae::TextObject>("Programming 4 Assignment", font);
	auto to = std::make_unique<dae::GameObject>();
 	to->AddComponent<dae::TextComponent>();
	to->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 22);
	to->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	
	//to->SetPosition(80, 20);
	scene.Add(std::move(to));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}