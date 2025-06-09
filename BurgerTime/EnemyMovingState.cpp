#include "EnemyMovingState.h"

std::unique_ptr<game::EnemyState> game::EnemyMovingState::HandleState(dae::GameObject&)
{
	// TODO: check if Enemy is stunned
	// TODO: check if Enemy is Squished
	
	return nullptr;
	//return std::unique_ptr<EnemyState>();
}
