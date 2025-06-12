#include "LeaderboardState.h"
#include "SceneManager.h"
#include "UILoader.h"
#include "InputManager.h"
#include "MenuCommands.h"
#include "CursorComponent.h"
#include "GameModeComponent.h"
#include "CommandLoader.h"

void game::LeaderboardState::OnEnter(dae::GameObject*)
{
	auto scene = dae::SceneManager::GetInstance().CreateScene("leaderboard");
	UILoader::GetInstance().LoadLeaderBoardUI(scene);
	
	auto gamemode = dae::SceneManager::GetInstance().GetGameMode();
	auto cursor = scene->GetObjectByTag("^");
	cursor->GetComponent<game::CursorComponent>()->AddObserver(gamemode->GetComponent<game::GameModeComponent>());

	CommandLoader::GetInstance().CreateLeaderboardCommands(scene);

	dae::SceneManager::GetInstance().SetActiveScene("leaderboard");
}
