#include "CommandLoader.h"
#include "InputManager.h"
#include "MenuCommands.h"
#include "GameCommand.h"

void game::CommandLoader::CreateStartMenuCommands(dae::Scene* pScene)
{
	auto cursor = pScene->GetObjectByTag(">");
	auto menuComp = pScene->GetObjectByTag("menu")->GetComponent<game::MenuComponent>();

	auto confirmCommand = std::make_unique<game::MenuConfirmCommand>(cursor, pScene->GetObjectByTag("menu"));
	auto menuMoveUpCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{ 0.f, -1.f });
	auto menuMoveDownCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{ 0.f, 1.f });

	dae::InputManager::GetInstance().BindCommand(std::move(confirmCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::BUTTON_A);
	dae::InputManager::GetInstance().BindCommand(std::move(menuMoveUpCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_UP);
	dae::InputManager::GetInstance().BindCommand(std::move(menuMoveDownCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_DOWN);

    auto keyboardConfirmCommand = std::make_unique<game::MenuConfirmCommand>(cursor, pScene->GetObjectByTag("menu"));
    auto keyboardmenuMoveUpCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{ 0.f, -1.f });
    auto keyboardMenuMoveDownCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{ 0.f, 1.f });

    dae::InputManager::GetInstance().BindCommand(std::move(keyboardConfirmCommand), dae::InputState::Released, SDL_SCANCODE_E);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardmenuMoveUpCommand), dae::InputState::Released, SDL_SCANCODE_W);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMenuMoveDownCommand), dae::InputState::Released, SDL_SCANCODE_S);
}

void game::CommandLoader::CreateSinglePlayerCommands(dae::Scene* pScene, dae::GameObject* pGameState)
{
    auto player = pScene->GetObjectByTag("player0");
    float speed = 100.f;

    auto moveLeftCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec3(-1, 0, 0));
    auto moveRightCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec3(1, 0, 0));
    auto moveUpCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec3(0, -1, 0));
    auto moveDownCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec3(0, 1, 0));
    auto ThrowPepperCommand = std::make_unique<game::ThrowPepperCommand>(player);

    // controller bindings
    dae::InputManager::GetInstance().BindCommand(std::move(moveLeftCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_LEFT);
    dae::InputManager::GetInstance().BindCommand(std::move(moveRightCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_RIGHT);
    dae::InputManager::GetInstance().BindCommand(std::move(moveUpCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_UP);
    dae::InputManager::GetInstance().BindCommand(std::move(moveDownCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_DOWN);
    dae::InputManager::GetInstance().BindCommand(std::move(ThrowPepperCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::BUTTON_B);

    auto keyboardMoveLeftCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec3(-1, 0, 0));
    auto keyboardMoveRightCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec3(1, 0, 0));
    auto keyboardMoveUpCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec3(0, -1, 0));
    auto keyboardMoveDownCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec3(0, 1, 0));
    auto keyboardThrowPepperCommand = std::make_unique<game::ThrowPepperCommand>(player);
    auto SkipLevelCommand = std::make_unique<game::SkipLevel>(pGameState);

    // keyboard bindings
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveLeftCommand), dae::InputState::Held, SDL_SCANCODE_A);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveRightCommand), dae::InputState::Held, SDL_SCANCODE_D);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveUpCommand), dae::InputState::Held, SDL_SCANCODE_W);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveDownCommand), dae::InputState::Held, SDL_SCANCODE_S);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardThrowPepperCommand), dae::InputState::Released, SDL_SCANCODE_E);
    dae::InputManager::GetInstance().BindCommand(std::move(SkipLevelCommand), dae::InputState::Released, SDL_SCANCODE_F1);
}

void game::CommandLoader::CreateLeaderboardCommands(dae::Scene* pScene)
{
    auto cursor = pScene->GetObjectByTag("^");
    auto menuComp = pScene->GetObjectByTag("menu")->GetComponent<game::MenuComponent>();
    
    auto confirmCommand = std::make_unique<game::MenuConfirmCommand>(cursor, pScene->GetObjectByTag("menu"));
    auto menuMoveLeftCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{ -1.f, 0.f });
    auto menuMoveRigthCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{ 1.f, 0.f });
    auto incrementLetterCommand = std::make_unique<ChangeLetterCommand>(cursor, menuComp, glm::vec2{ 0.f, 1.f });
    auto decrementLetterCommand = std::make_unique<ChangeLetterCommand>(cursor, menuComp, glm::vec2{ 0.f, -1.f });

    dae::InputManager::GetInstance().BindCommand(std::move(confirmCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::BUTTON_A);
    dae::InputManager::GetInstance().BindCommand(std::move(menuMoveLeftCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_LEFT);
    dae::InputManager::GetInstance().BindCommand(std::move(menuMoveRigthCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_RIGHT);
    dae::InputManager::GetInstance().BindCommand(std::move(incrementLetterCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_DOWN);
    dae::InputManager::GetInstance().BindCommand(std::move(decrementLetterCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::DPAD_UP);

    auto keyboardConfirmCommand = std::make_unique<game::MenuConfirmCommand>(cursor, pScene->GetObjectByTag("menu"));
    auto keyboardMenuMoveLeftCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{ -1.f, 0.f });
    auto keyboardMenuMoveRigthCommand = std::make_unique<game::MenuMoveCommand>(cursor, menuComp, glm::vec2{ 1.f, 0.f });
    auto keyboardIncrementLetterCommand = std::make_unique<ChangeLetterCommand>(cursor, menuComp, glm::vec2{ 0.f, 1.f });
    auto keyboardDecrementLetterCommand = std::make_unique<ChangeLetterCommand>(cursor, menuComp, glm::vec2{ 0.f, -1.f });

    dae::InputManager::GetInstance().BindCommand(std::move(keyboardConfirmCommand), dae::InputState::Released, SDL_SCANCODE_E);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMenuMoveLeftCommand), dae::InputState::Released, SDL_SCANCODE_A);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMenuMoveRigthCommand), dae::InputState::Released, SDL_SCANCODE_D);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardIncrementLetterCommand), dae::InputState::Released, SDL_SCANCODE_S);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardDecrementLetterCommand), dae::InputState::Released, SDL_SCANCODE_W);
}
