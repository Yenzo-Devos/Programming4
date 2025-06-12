#include "CoopGameState.h"
#include "LeaderboardState.h"
#include "SceneManager.h"
#include "GameModeComponent.h"
#include "LevelLoader.h"
#include "CommandLoader.h"
#include "UILoader.h"
#include "CollisionHandler.h"
#include "InputManager.h"
#include "PointsComponent.h"
#include "LivesComponent.h"
#include "PepperComponent.h"
#include "PlayerComponent.h"

std::unique_ptr<game::GameState> game::CoopGameState::HandleState(dae::GameObject*)
{
	if (m_GameHasEnded)
		return std::make_unique<LeaderboardState>();

	return nullptr;
}

void game::CoopGameState::OnEnter(dae::GameObject* owner)
{
	auto scene = dae::SceneManager::GetInstance().CreateScene("co-op");
	auto playerData = owner->GetComponent<GameModeComponent>()->GetPlayerData();
	LevelLoader::GetInstance().LoadLevel("../Data/", "levels/level1.json", scene, playerData, 1);

	UILoader::GetInstance().LoadGameUI(scene);
	CommandLoader::GetInstance().CreateCoopCommands(scene, owner);
	dae::CollisionHandler::GetInstance().Init();
	dae::SceneManager::GetInstance().SetActiveScene("co-op");
}

void game::CoopGameState::OnExit(dae::GameObject*)
{
	dae::InputManager::GetInstance().UnBindGamePadCommands();
	dae::InputManager::GetInstance().UnBindKeyboardCommands();
}

void game::CoopGameState::LoadNextLevel(dae::GameObject* owner)
{
	++m_Level;
	m_Level = ((m_Level - 1) % 3) + 1;
	auto scene = dae::SceneManager::GetInstance().GetActiveScene();
	GameModeComponent::PlayerData playerData = CreateBufferPlayerData(scene);
	owner->GetComponent<GameModeComponent>()->SetPlayerData(playerData);
	RemoveAllObjects();

	std::string levelName = "levels/level" + std::to_string(m_Level) + ".json";
	LevelLoader::GetInstance().LoadLevel("../Data/", levelName, scene, playerData, 1);

	UILoader::GetInstance().LoadGameUI(scene);
	CommandLoader::GetInstance().CreateCoopCommands(scene, owner);
	dae::CollisionHandler::GetInstance().Init();
}

game::GameModeComponent::PlayerData game::CoopGameState::CreateBufferPlayerData(dae::Scene* pScene)
{
	auto player = pScene->GetObjectByTag("player0");
	GameModeComponent::PlayerData playerData{ };
	playerData.score = player->GetComponent<PointsComponent>()->GetCurrentPoints();
	playerData.lives = player->GetComponent<LivesComponent>()->GetCurrentNrOfLives();
	playerData.nrOfPepper = player->GetComponent<PlayerComponent>()->GetPepper()->GetComponent<PepperComponent>()->GetPepperCount();
	return playerData;
}

void game::CoopGameState::RemoveAllObjects()
{
	dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
	dae::InputManager::GetInstance().UnBindGamePadCommands();
	dae::InputManager::GetInstance().UnBindKeyboardCommands();
}
