#include "EnemyStunnedState.h"
#include "EnemyChaseState.h"

void game::EnemyStunnedState::Update(float deltaTime)
{
    m_AccuStunTime += deltaTime;
}

std::unique_ptr<game::EnemyState> game::EnemyStunnedState::HandleState(dae::GameObject&)
{
    // check if hit by ingredient falling
    // return DeadState

    if (m_AccuStunTime >= m_StunTime)
        return std::make_unique<EnemyChaseState>();

    return nullptr;
}

void game::EnemyStunnedState::OnEnter(dae::GameObject& owner)
{
    owner.GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("sprayed");
}
