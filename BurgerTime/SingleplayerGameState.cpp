#include "SingleplayerGameState.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "LevelLoader.h"
#include "CollisionHandler.h"
#include "GameCommand.h"
#include "UILoader.h"
#include "LeaderboardState.h"
#include "PointsComponent.h"
#include "LivesComponent.h"
#include "PepperComponent.h"
#include "PlayerComponent.h"
#include "HitboxComponent.h"
#include "CommandLoader.h"

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
    auto scene = dae::SceneManager::GetInstance().CreateScene("singleplayer");
    auto playerData = owner->GetComponent<GameModeComponent>()->GetPlayerData();
    LevelLoader::GetInstance().LoadLevel("../Data/", "levels/level1.json", scene, playerData);

    UILoader::GetInstance().LoadGameUI(scene);
    CommandLoader::GetInstance().CreateSinglePlayerCommands(scene, owner);
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
    GameModeComponent::PlayerData playerData = CreateBufferPlayerData(scene);
    owner->GetComponent<GameModeComponent>()->SetPlayerData(playerData);
    RemoveAllObjects();
    
    std::string levelName = "levels/level" + std::to_string(m_Level) + ".json";
    LevelLoader::GetInstance().LoadLevel("../Data/", levelName, scene, playerData);
    
    UILoader::GetInstance().LoadGameUI(scene);
    CommandLoader::GetInstance().CreateSinglePlayerCommands(scene, owner);
    dae::CollisionHandler::GetInstance().Init();
}

game::GameModeComponent::PlayerData game::SingleplayerGameState::CreateBufferPlayerData(dae::Scene* pScene)
{
    auto player = pScene->GetObjectByTag("player0");
    GameModeComponent::PlayerData playerData{ };
    playerData.score = player->GetComponent<PointsComponent>()->GetCurrentPoints();
    playerData.lives = player->GetComponent<LivesComponent>()->GetCurrentNrOfLives();
    playerData.nrOfPepper = player->GetComponent<PlayerComponent>()->GetPepper()->GetComponent<PepperComponent>()->GetPepperCount();
    return playerData;
}

void game::SingleplayerGameState::RemoveAllObjects()
{
    dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
    dae::InputManager::GetInstance().UnBindGamePadCommands();
    dae::InputManager::GetInstance().UnBindKeyboardCommands();
}
