#include "EnemyChaseState.h"
#include "EnemyStunnedState.h"

std::unique_ptr<game::EnemyState> game::EnemyChaseState::HandleState(dae::GameObject&)
{
	// TODO: check if Enemy is stunned
	if (m_IsStunned)
		return std::make_unique<EnemyStunnedState>();
	// TODO: check if Enemy is Squished
	// TODO: check if Enemy is Falling

	return nullptr;
	//return std::unique_ptr<EnemyState>();
}
