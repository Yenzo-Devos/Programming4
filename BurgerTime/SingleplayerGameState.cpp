#include "SingleplayerGameState.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "LevelLoader.h"
#include "CollisionHandler.h"
#include "GameCommand.h"
#include "UILoader.h"
#include "LeaderboardState.h"
#include "GameModeComponent.h"
#include "PointsComponent.h"
#include "LivesComponent.h"
#include "PepperComponent.h"
#include "PlayerComponent.h"
#include "HitboxComponent.h"

#include <iostream>

std::unique_ptr<game::GameState> game::SingleplayerGameState::HandleState(dae::GameObject*)
{
    // on death go to leaderboard
    if (m_GameHasEnded)
        return std::make_unique<LeaderboardState>();

    return nullptr;
}

void game::SingleplayerGameState::OnEnter(dae::GameObject* owner)
{
    auto gamemode = owner->GetComponent<GameModeComponent>();
    auto scene = dae::SceneManager::GetInstance().CreateScene("singleplayer");
    LevelLoader::GetInstance().LoadLevel("../Data/", "levels/level1.json", scene);

    auto player = scene->GetObjectByTag("player0");
    player->AddComponent<PointsComponent>(gamemode->GetPlayerData().score);
    player->AddComponent<LivesComponent>(gamemode->GetPlayerData().lives);
    auto pepperHitbox = player->GetComponent<PlayerComponent>()->GetPepper()->GetComponent<dae::HitboxComponent>();
    player->GetComponent<PlayerComponent>()->GetPepper()->AddComponent<PepperComponent>(pepperHitbox,gamemode->GetPlayerData().nrOfPepper);

    UILoader::GetInstance().LoadGameUI(scene);
    CreateCommands(scene, owner);
    dae::CollisionHandler::GetInstance().Init();
    dae::SceneManager::GetInstance().SetActiveScene("singleplayer");
}

void game::SingleplayerGameState::OnExit(dae::GameObject*)
{
    dae::InputManager::GetInstance().UnBindGamePadCommands();
    dae::InputManager::GetInstance().UnBindKeyboardCommands();
}

void game::SingleplayerGameState::LoadNextLevel(dae::GameObject* owner)
{
    ++m_Level;
    m_Level = ((m_Level - 1) % 3) + 1;
    auto scene = dae::SceneManager::GetInstance().GetActiveScene();
    auto player = scene->GetObjectByTag("player0");
    GameModeComponent::PlayerData playerData{ };
    playerData.score = player->GetComponent<PointsComponent>()->GetCurrentPoints();
    playerData.lives = player->GetComponent<LivesComponent>()->GetCurrentNrOfLives();
    playerData.nrOfPepper = player->GetComponent<PlayerComponent>()->GetPepper()->GetComponent<PepperComponent>()->GetPepperCount();
    owner->GetComponent<GameModeComponent>()->SetPlayerData(playerData);

    dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
    dae::InputManager::GetInstance().UnBindGamePadCommands();
    dae::InputManager::GetInstance().UnBindKeyboardCommands();
    std::string levelName = "levels/level" + std::to_string(m_Level) + ".json";
    LevelLoader::GetInstance().LoadLevel("../Data/", levelName, scene);
    // make sure the player gets correctly made
    auto newPlayer = scene->GetObjectByTag("player0");
    newPlayer->AddComponent<PointsComponent>(playerData.score);
    newPlayer->AddComponent<LivesComponent>(playerData.lives);
    auto pepperHitbox = newPlayer->GetComponent<PlayerComponent>()->GetPepper()->GetComponent<dae::HitboxComponent>();
    newPlayer->GetComponent<PlayerComponent>()->GetPepper()->AddComponent<PepperComponent>(pepperHitbox, playerData.nrOfPepper);

    UILoader::GetInstance().LoadGameUI(scene);
    CreateCommands(scene, owner);
    dae::CollisionHandler::GetInstance().Init();
}

void game::SingleplayerGameState::CreateCommands(dae::Scene* pScene, dae::GameObject* owner)
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
    auto SkipLevelCommand = std::make_unique<game::SkipLevel>(owner);

    // keyboard bindings
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveLeftCommand), dae::InputState::Held, SDL_SCANCODE_A);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveRightCommand), dae::InputState::Held, SDL_SCANCODE_D);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveUpCommand), dae::InputState::Held, SDL_SCANCODE_W);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardMoveDownCommand), dae::InputState::Held, SDL_SCANCODE_S);
    dae::InputManager::GetInstance().BindCommand(std::move(keyboardThrowPepperCommand), dae::InputState::Released, SDL_SCANCODE_E);
    dae::InputManager::GetInstance().BindCommand(std::move(SkipLevelCommand), dae::InputState::Released, SDL_SCANCODE_F1);
}
