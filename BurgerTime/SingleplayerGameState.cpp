#include "SingleplayerGameState.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "LevelLoader.h"
#include "CollisionHandler.h"
#include "GameCommand.h"
#include "UILoader.h"
#include "LeaderboardState.h"

std::unique_ptr<game::GameState> game::SingleplayerGameState::HandleState(dae::GameObject&)
{
    // on death go to leaderboard
    if (m_GameHasEnded)
        return std::make_unique<LeaderboardState>();

    return nullptr;
}

void game::SingleplayerGameState::OnEnter(dae::GameObject&)
{
    auto scene = dae::SceneManager::GetInstance().CreateScene("singleplayer");
    LevelLoader::GetInstance().LoadLevel("../Data/", "levels/level1.json", scene);
    UILoader::GetInstance().LoadGameUI(scene);
    CreateCommands(scene);
    dae::CollisionHandler::GetInstance().Init();
    dae::SceneManager::GetInstance().SetActiveScene("singleplayer");
}

void game::SingleplayerGameState::OnExit(dae::GameObject&)
{
    dae::InputManager::GetInstance().UnBindGamePadCommands();
    dae::InputManager::GetInstance().UnBindKeyboardCommands();
}

void game::SingleplayerGameState::LoadNextLevel()
{
    //++m_Level %= 3;
}

void game::SingleplayerGameState::CreateCommands(dae::Scene* pScene)
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

    // keyboard bindings
    dae::InputManager::GetInstance().BindCommand(std::move(moveLeftCommand), dae::InputState::Held, SDL_SCANCODE_A);
    dae::InputManager::GetInstance().BindCommand(std::move(moveRightCommand), dae::InputState::Held, SDL_SCANCODE_D);
    dae::InputManager::GetInstance().BindCommand(std::move(moveUpCommand), dae::InputState::Held, SDL_SCANCODE_W);
    dae::InputManager::GetInstance().BindCommand(std::move(moveDownCommand), dae::InputState::Held, SDL_SCANCODE_S);
    dae::InputManager::GetInstance().BindCommand(std::move(ThrowPepperCommand), dae::InputState::Released, SDL_SCANCODE_E);
}
