#include "StartScreenState.h"
#include "PlayGameState.h"
#include "SinglePlayerGameState.h"
#include "CoopGameState.h"
#include "VersusGameState.h"
#include "LeaderboardState.h"
#include "InputManager.h"

std::unique_ptr<game::GameState> game::StartScreenState::HandleState(dae::GameObject*)
{
	if (m_ModeSelected)
		return std::make_unique<PlayGameState>(m_ItemIndex);
	
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
