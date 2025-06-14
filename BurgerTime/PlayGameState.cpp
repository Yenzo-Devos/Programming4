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

void game::PlayGameState::Update(float deltaTime)
{
	if (m_ObjectsDeleted)
		m_AccuFrameTime += deltaTime;
}

std::unique_ptr<game::GameState> game::PlayGameState::HandleState(dae::GameObject* owner)
{
	if (m_GameHasEnded)
		return std::make_unique<LeaderboardState>();

	if (m_ObjectsDeleted && m_AccuFrameTime > m_FrameTime)
	{
		ActualLoadingOfObjects(owner);
		m_AccuFrameTime = 0.f;
	}
	return nullptr;
}

void game::PlayGameState::OnEnter(dae::GameObject* owner)
{
	auto scene = dae::SceneManager::GetInstance().CreateScene(m_SceneNames[m_GameModeIndex]);
	auto playerData = owner->GetComponent<GameModeComponent>()->GetPlayerData();
	
	LevelLoader::GetInstance().LoadLevel("../Data/", "levels/level1.json", scene, playerData, m_GameModeIndex);
	UILoader::GetInstance().LoadGameUI(scene);
	CommandLoader::GetInstance().CreateGameCommand(scene, owner, m_GameModeIndex);
	game::CollisionHandler::GetInstance().Init();
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

bool game::PlayGameState::LoadNextLevel(dae::GameObject*)
{
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.StopMusic();
	ss.PlayMusic("../Data/sounds/BGM.wav", -1);

	++m_Level;
	m_Level = ((m_Level - 1) % 3) + 1;
	auto scene = dae::SceneManager::GetInstance().GetActiveScene();
	m_BufferPlayerData = CreateBufferPlayerData(scene);
	
	RemoveAllObjects();
	return true;
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

void game::PlayGameState::ActualLoadingOfObjects(dae::GameObject* owner)
{
	auto scene = dae::SceneManager::GetInstance().GetActiveScene();
	owner->GetComponent<GameModeComponent>()->SetPlayerData(m_BufferPlayerData);
	std::string levelName = "levels/level" + std::to_string(m_Level) + ".json";
	LevelLoader::GetInstance().LoadLevel("../Data/", levelName, scene, m_BufferPlayerData, m_GameModeIndex);
	UILoader::GetInstance().LoadGameUI(scene);
	CommandLoader::GetInstance().CreateGameCommand(scene, owner, m_GameModeIndex);
	game::CollisionHandler::GetInstance().Init();
	m_ObjectsDeleted = false;
}

void game::PlayGameState::RemoveAllObjects()
{
	dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
	dae::InputManager::GetInstance().UnBindGamePadCommands();
	dae::InputManager::GetInstance().UnBindKeyboardCommands();
}
