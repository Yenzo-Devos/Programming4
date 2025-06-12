#include "LeaderboardState.h"
#include "SceneManager.h"
#include "UILoader.h"
#include "InputManager.h"
#include "MenuCommands.h"
#include "CursorComponent.h"
#include "GameModeComponent.h"

void game::LeaderboardState::OnEnter(dae::GameObject&)
{
	auto scene = dae::SceneManager::GetInstance().CreateScene("leaderboard");
	UILoader::GetInstance().LoadLeaderBoardUI(scene);
	// load the commands
	CreateCommands(scene);

	dae::SceneManager::GetInstance().SetActiveScene("leaderboard");
}

void game::LeaderboardState::CreateCommands(dae::Scene* scene)
{
	auto gamemode = dae::SceneManager::GetInstance().GetGameMode();
	auto cursor = scene->GetObjectByTag("^");
	cursor->GetComponent<game::CursorComponent>()->AddObserver(gamemode->GetComponent<game::GameModeComponent>());

	auto menuComp = scene->GetObjectByTag("menu")->GetComponent<game::MenuComponent>();
	auto confirmCommand = std::make_unique<game::MenuConfirmCommand>(cursor, scene->GetObjectByTag("menu"));
	auto menuMoveLeftCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{ -1.f, 0.f });
	auto menuMoveRigthCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{ 1.f, 0.f });
	auto incrementLetterCommand = std::make_unique<ChangeLetterCommand>(cursor, menuComp, glm::vec2{ 0.f, 1.f });
	auto decrementLetterCommand = std::make_unique<ChangeLetterCommand>(cursor, menuComp, glm::vec2{ 0.f, -1.f });
	
	dae::InputManager::GetInstance().BindCommand(std::move(confirmCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::BUTTON_A);
	dae::InputManager::GetInstance().BindCommand(std::move(menuMoveLeftCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_LEFT);
	dae::InputManager::GetInstance().BindCommand(std::move(menuMoveRigthCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_RIGHT);
	dae::InputManager::GetInstance().BindCommand(std::move(incrementLetterCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_DOWN);
	dae::InputManager::GetInstance().BindCommand(std::move(decrementLetterCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_UP);
}
