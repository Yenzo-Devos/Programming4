#include "LeaderboardState.h"
#include "SceneManager.h"
#include "UILoader.h"

void game::LeaderboardState::OnEnter(dae::GameObject&)
{
	auto scene = dae::SceneManager::GetInstance().CreateScene("leaderboard");
	UILoader::GetInstance().LoadLeaderBoardUI(scene);
	// load the commands

	auto gamemode = dae::SceneManager::GetInstance().GetActiveScene()->GetGameMode();
	dae::SceneManager::GetInstance().SetActiveScene("leaderboard", std::move(gamemode));
}
