#include "EnemySquishedState.h"

std::unique_ptr<game::EnemyState> game::EnemySquishedState::HandleState(dae::GameObject&)
{
    // after a certain point go to dead state
    // return deadState
    return nullptr;
}
