#include "StartScreenState.h"
#include "SinglePlayerGameState.h"
#include "CoopGameState.h"
#include "VersusGameState.h"
#include "LeaderboardState.h"

std::unique_ptr<game::GameState> game::StartScreenState::HandleState(dae::GameObject&)
{
	if (!m_ModeSelected)
		return nullptr;

	if (m_CursorHeight == 200.f)
		return std::make_unique<LeaderboardState>();
	if (m_CursorHeight == 250.f)
		return std::make_unique<CoopGameState>();
	if (m_CursorHeight == 300.f)
		return std::make_unique<VersusGameState>();

	return nullptr;
}

void game::StartScreenState::ModeSelected(glm::vec3 pos)
{
	m_CursorHeight = pos.y;
}
