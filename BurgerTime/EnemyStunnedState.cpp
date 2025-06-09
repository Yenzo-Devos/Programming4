#include "EnemyStunnedState.h"
#include "EnemyMovingState.h"

void game::EnemyStunnedState::Update(float deltaTime)
{
    m_AccuStunTime += m_StunTime;
}

std::unique_ptr<game::EnemyState> game::EnemyStunnedState::HandleState(dae::GameObject&)
{
    // check if hit by ingredient falling
    // return DeadState

    if (m_AccuStunTime >= m_StunTime)
        return std::make_unique<EnemyMovingState>();

    return nullptr;
}
