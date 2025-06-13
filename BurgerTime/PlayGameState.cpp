#include "PlayGameState.h"
#include "LeaderboardState.h"
#include "SceneManager.h"
#include "LevelLoader.h"
#include "UILoader.h"
#include "CommandLoader.h"
#include "CollisionHandler.h"
#include "InputManager.h"
#include "PointsComponent.h"
#include "LivesComponent.h"
#include "PlayerComponent.h"
#include "PepperComponent.h"
#include "ServiceLocator.h"

game::PlayGameState::PlayGameState(int gameModeIndex)
	: m_GameModeIndex{ gameModeIndex }
{
}

std::unique_ptr<game::GameState> game::PlayGameState::HandleState(dae::GameObject*)
{
	if (m_GameHasEnded)
		return std::make_unique<LeaderboardState>();

	return nullptr;
}

void game::PlayGameState::OnEnter(dae::GameObject* owner)
{
	auto scene = dae::SceneManager::GetInstance().CreateScene(m_SceneNames[m_GameModeIndex]);
	auto playerData = owner->GetComponent<GameModeComponent>()->GetPlayerData();
	
	LevelLoader::GetInstance().LoadLevel("../Data/", "levels/level1.json", scene, playerData, m_GameModeIndex);
	UILoader::GetInstance().LoadGameUI(scene);
	CommandLoader::GetInstance().CreateGameCommand(scene, owner, m_GameModeIndex);
	dae::CollisionHandler::GetInstance().Init();
	dae::SceneManager::GetInstance().SetActiveScene(m_SceneNames[m_GameModeIndex]);

	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.PlayMusic("../Data/sounds/BGM.wav", -1);
}

void game::PlayGameState::OnExit(dae::GameObject*)
{
	dae::InputManager::GetInstance().UnBindGamePadCommands();
	dae::InputManager::GetInstance().UnBindKeyboardCommands();
	
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.StopMusic();
}

void game::PlayGameState::LoadNextLevel(dae::GameObject* owner)
{
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.PlayMusic("../Data/sounds/BGM.wav", -1);

	++m_Level;
	m_Level = ((m_Level - 1) % 3) + 1;
	auto scene = dae::SceneManager::GetInstance().GetActiveScene();
	GameModeComponent::PlayerData playerData = CreateBufferPlayerData(scene);
	owner->GetComponent<GameModeComponent>()->SetPlayerData(playerData);
	RemoveAllObjects();

	std::string levelName = "levels/level" + std::to_string(m_Level) + ".json";
	LevelLoader::GetInstance().LoadLevel("../Data/", levelName, scene, playerData, m_GameModeIndex);
	UILoader::GetInstance().LoadGameUI(scene);
	CommandLoader::GetInstance().CreateGameCommand(scene, owner, m_GameModeIndex);
	dae::CollisionHandler::GetInstance().Init();
}

game::GameModeComponent::PlayerData game::PlayGameState::CreateBufferPlayerData(dae::Scene* pScene)
{
	auto player = pScene->GetObjectByTag("player0");
	GameModeComponent::PlayerData playerData{ };
	playerData.score = player->GetComponent<PointsComponent>()->GetCurrentPoints();
	playerData.lives = player->GetComponent<LivesComponent>()->GetCurrentNrOfLives();
	playerData.nrOfPepper = player->GetComponent<PlayerComponent>()->GetPepper()->GetComponent<PepperComponent>()->GetPepperCount();
	return playerData;
}

void game::PlayGameState::RemoveAllObjects()
{
	dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
	dae::InputManager::GetInstance().UnBindGamePadCommands();
	dae::InputManager::GetInstance().UnBindKeyboardCommands();
}
