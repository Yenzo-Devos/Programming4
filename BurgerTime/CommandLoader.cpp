#include "CommandLoader.h"
#include "InputManager.h"
#include "MenuCommands.h"
#include "GameCommand.h"
#include "ChaseComponent.h"

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

void game::CommandLoader::CreateGameCommand(dae::Scene* pScene, dae::GameObject* pGameState, int gameModeIndex)
{
    if (gameModeIndex == 0)
    {
        CreateSinglePlayerCommands(pScene, pGameState);
        return;
    }
    else if (gameModeIndex == 1)
    {
        CreateCoopCommands(pScene, pGameState);
        return;
    }
    else if (gameModeIndex == 2)
        CreateVersusCommands(pScene, pGameState);
}

void game::CommandLoader::CreateSinglePlayerCommands(dae::Scene* pScene, dae::GameObject* pGameState)
{
    auto player = pScene->GetObjectByTag("player0");
    float speed = 100.f;

    auto moveLeftCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ -1, 0 });
    auto moveRightCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ 1, 0 });
    auto moveUpCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, -1 });
    auto moveDownCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, 1 });
    auto throwPepperCommand = std::make_unique<game::ThrowPepperCommand>(player);

    // controller bindings
    dae::InputManager::GetInstance().BindCommand(std::move(moveLeftCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_LEFT);
    dae::InputManager::GetInstance().BindCommand(std::move(moveRightCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_RIGHT);
    dae::InputManager::GetInstance().BindCommand(std::move(moveUpCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_UP);
    dae::InputManager::GetInstance().BindCommand(std::move(moveDownCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_DOWN);
    dae::InputManager::GetInstance().BindCommand(std::move(throwPepperCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::BUTTON_B);

    auto keyboardMoveLeftCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ -1, 0 });
    auto keyboardMoveRightCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ 1, 0 });
    auto keyboardMoveUpCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, -1 });
    auto keyboardMoveDownCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, 1 });
    auto keyboardThrowPepperCommand = std::make_unique<game::ThrowPepperCommand>(player);
    auto skipLevelCommand = std::make_unique<game::SkipLevelCommand>(pGameState);
    auto muteCommand = std::make_unique<game::MuteSoundCommand>();

    // keyboard bindings
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveLeftCommand), dae::InputState::Held, SDL_SCANCODE_A);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveRightCommand), dae::InputState::Held, SDL_SCANCODE_D);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveUpCommand), dae::InputState::Held, SDL_SCANCODE_W);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveDownCommand), dae::InputState::Held, SDL_SCANCODE_S);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardThrowPepperCommand), dae::InputState::Released, SDL_SCANCODE_E);
    dae::InputManager::GetInstance().BindCommand(std::move(skipLevelCommand), dae::InputState::Released, SDL_SCANCODE_F1);
    dae::InputManager::GetInstance().BindCommand(std::move(muteCommand), dae::InputState::Released, SDL_SCANCODE_F2);
}

void game::CommandLoader::CreateCoopCommands(dae::Scene* pScene, dae::GameObject* pGameState)
{
    auto player = pScene->GetObjectByTag("player0");
    auto otherPlayer = pScene->GetObjectByTag("player1");
    float speed = 100.f;

    auto moveLeftCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ -1, 0 });
    auto moveRightCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ 1, 0 });
    auto moveUpCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, -1 });
    auto moveDownCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, 1 });
    auto throwPepperCommand = std::make_unique<game::ThrowPepperCommand>(player);

    auto otherMoveLeftCommand = std::make_unique<game::MoveCommand>(otherPlayer, speed, glm::vec2{ -1, 0 });
    auto otherMoveRightCommand = std::make_unique<game::MoveCommand>(otherPlayer, speed, glm::vec2{ 1, 0 });
    auto otherMoveUpCommand = std::make_unique<game::MoveCommand>(otherPlayer, speed / 2, glm::vec2{ 0, -1 });
    auto otherMoveDownCommand = std::make_unique<game::MoveCommand>(otherPlayer, speed / 2, glm::vec2{ 0, 1 });
    auto otherThrowPepperCommand = std::make_unique<game::ThrowPepperCommand>(otherPlayer);

    // controller bindings
    dae::InputManager::GetInstance().BindCommand(std::move(moveLeftCommand), 1, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_LEFT);
    dae::InputManager::GetInstance().BindCommand(std::move(moveRightCommand), 1, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_RIGHT);
    dae::InputManager::GetInstance().BindCommand(std::move(moveUpCommand), 1, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_UP);
    dae::InputManager::GetInstance().BindCommand(std::move(moveDownCommand), 1, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_DOWN);
    dae::InputManager::GetInstance().BindCommand(std::move(throwPepperCommand), 1, dae::InputState::Released, dae::GamePad::GamePadButton::BUTTON_B);

    dae::InputManager::GetInstance().BindCommand(std::move(otherMoveLeftCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_LEFT);
    dae::InputManager::GetInstance().BindCommand(std::move(otherMoveRightCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_RIGHT);
    dae::InputManager::GetInstance().BindCommand(std::move(otherMoveUpCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_UP);
    dae::InputManager::GetInstance().BindCommand(std::move(otherMoveDownCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_DOWN);
    dae::InputManager::GetInstance().BindCommand(std::move(otherThrowPepperCommand), 0, dae::InputState::Released, dae::GamePad::GamePadButton::BUTTON_B);

    auto keyboardMoveLeftCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ -1, 0 });
    auto keyboardMoveRightCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ 1, 0 });
    auto keyboardMoveUpCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, -1 });
    auto keyboardMoveDownCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, 1 });
    auto keyboardThrowPepperCommand = std::make_unique<game::ThrowPepperCommand>(player);
    auto skipLevelCommand = std::make_unique<game::SkipLevelCommand>(pGameState);
    auto muteCommand = std::make_unique<game::MuteSoundCommand>();

    // keyboard bindings
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveLeftCommand), dae::InputState::Held, SDL_SCANCODE_A);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveRightCommand), dae::InputState::Held, SDL_SCANCODE_D);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveUpCommand), dae::InputState::Held, SDL_SCANCODE_W);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveDownCommand), dae::InputState::Held, SDL_SCANCODE_S);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardThrowPepperCommand), dae::InputState::Released, SDL_SCANCODE_E);
    dae::InputManager::GetInstance().BindCommand(std::move(skipLevelCommand), dae::InputState::Released, SDL_SCANCODE_F1);
    dae::InputManager::GetInstance().BindCommand(std::move(muteCommand), dae::InputState::Released, SDL_SCANCODE_F2);
}

void game::CommandLoader::CreateVersusCommands(dae::Scene* pScene, dae::GameObject* pGameState)
{
    dae::GameObject* controlledEnemy{};
    auto enemyVec = pScene->GetAllObjectByTag("enemy");
    for (auto enemy : enemyVec)
    {
        if (enemy->GetComponent<ChaseComponent>()->GetIsOwnerControlled())
            controlledEnemy = enemy;
    }

    auto player = pScene->GetObjectByTag("player0");
    float speed = 100.f;

    auto moveLeftCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ -1, 0 });
    auto moveRightCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ 1, 0 });
    auto moveUpCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, -1 });
    auto moveDownCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, 1 });
    auto throwPepperCommand = std::make_unique<game::ThrowPepperCommand>(player);

    auto enemyMoveLeftCommand = std::make_unique<game::MoveCommand>(controlledEnemy, speed, glm::vec2{ -1, 0 });
    auto enemyMoveRightCommand = std::make_unique<game::MoveCommand>(controlledEnemy, speed, glm::vec2{ 1, 0 });
    auto enemyMoveUpCommand = std::make_unique<game::MoveCommand>(controlledEnemy, speed / 2, glm::vec2{ 0, -1 });
    auto enemyMoveDownCommand = std::make_unique<game::MoveCommand>(controlledEnemy, speed / 2, glm::vec2{ 0, 1 });

    // controller bindings
    dae::InputManager::GetInstance().BindCommand(std::move(moveLeftCommand), 1, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_LEFT);
    dae::InputManager::GetInstance().BindCommand(std::move(moveRightCommand), 1, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_RIGHT);
    dae::InputManager::GetInstance().BindCommand(std::move(moveUpCommand), 1, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_UP);
    dae::InputManager::GetInstance().BindCommand(std::move(moveDownCommand), 1, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_DOWN);
    dae::InputManager::GetInstance().BindCommand(std::move(throwPepperCommand), 1, dae::InputState::Released, dae::GamePad::GamePadButton::BUTTON_B);

    dae::InputManager::GetInstance().BindCommand(std::move(enemyMoveLeftCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_LEFT);
    dae::InputManager::GetInstance().BindCommand(std::move(enemyMoveRightCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_RIGHT);
    dae::InputManager::GetInstance().BindCommand(std::move(enemyMoveUpCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_UP);
    dae::InputManager::GetInstance().BindCommand(std::move(enemyMoveDownCommand), 0, dae::InputState::Held, dae::GamePad::GamePadButton::DPAD_DOWN);

    auto keyboardMoveLeftCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ -1, 0 });
    auto keyboardMoveRightCommand = std::make_unique<game::MoveCommand>(player, speed, glm::vec2{ 1, 0 });
    auto keyboardMoveUpCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, -1 });
    auto keyboardMoveDownCommand = std::make_unique<game::MoveCommand>(player, speed / 2, glm::vec2{ 0, 1 });
    auto keyboardThrowPepperCommand = std::make_unique<game::ThrowPepperCommand>(player);
    auto skipLevelCommand = std::make_unique<game::SkipLevelCommand>(pGameState);
    auto muteCommand = std::make_unique<game::MuteSoundCommand>();

    // keyboard bindings
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveLeftCommand), dae::InputState::Held, SDL_SCANCODE_A);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveRightCommand), dae::InputState::Held, SDL_SCANCODE_D);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveUpCommand), dae::InputState::Held, SDL_SCANCODE_W);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveDownCommand), dae::InputState::Held, SDL_SCANCODE_S);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardThrowPepperCommand), dae::InputState::Released, SDL_SCANCODE_E);
    dae::InputManager::GetInstance().BindCommand(std::move(skipLevelCommand), dae::InputState::Released, SDL_SCANCODE_F1);
    dae::InputManager::GetInstance().BindCommand(std::move(muteCommand), dae::InputState::Released, SDL_SCANCODE_F2);
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
