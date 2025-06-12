#include "StartScreenState.h"
#include "SinglePlayerGameState.h"
#include "CoopGameState.h"
#include "VersusGameState.h"
#include "LeaderboardState.h"
#include "InputManager.h"

std::unique_ptr<game::GameState> game::StartScreenState::HandleState(dae::GameObject*)
{
	if (!m_ModeSelected)
		return nullptr;

	if (m_ItemIndex == 0)
		return std::make_unique<SingleplayerGameState>();
	if (m_ItemIndex == 1)
		return std::make_unique<CoopGameState>();
	if (m_ItemIndex == 2)
		return std::make_unique<VersusGameState>();

	return nullptr;
}

void game::StartScreenState::OnExit(dae::GameObject*)
{
	dae::InputManager::GetInstance().UnBindGamePadCommands();
	dae::InputManager::GetInstance().UnBindKeyboardCommands();
}

void game::StartScreenState::ModeSelected(int itemIndex)
{
	m_ModeSelected = true;
	m_ItemIndex = itemIndex;
}
