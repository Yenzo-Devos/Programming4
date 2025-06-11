#include "EnemyStunnedState.h"
#include "EnemyChaseState.h"
#include "EnemyFallState.h"

void game::EnemyStunnedState::Update(float deltaTime)
{
    m_AccuStunTime += deltaTime;
}

std::unique_ptr<game::EnemyState> game::EnemyStunnedState::HandleState(dae::GameObject&)
{
    if (m_IsFalling)
        return std::make_unique<EnemyFallState>();

    if (m_AccuStunTime >= m_StunTime)
        return std::make_unique<EnemyChaseState>();

    return nullptr;
}

void game::EnemyStunnedState::OnEnter(dae::GameObject& owner)
{
    owner.GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("sprayed");
}
