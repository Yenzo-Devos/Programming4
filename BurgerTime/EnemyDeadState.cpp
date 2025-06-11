#include "EnemyDeadState.h"
#include "GameObject.h"
#include "RespawnComponent.h"
#include "EnemyChaseState.h"

void game::EnemyDeadState::Update(float deltaTime)
{
    m_AccuDeadTime += deltaTime;
}

std::unique_ptr<game::EnemyState> game::EnemyDeadState::HandleState(dae::GameObject& owner)
{
    if (m_AccuDeadTime >= m_DeadTime)
    {
        owner.GetComponent<RespawnComponent>()->RespawnOwner();
        return std::make_unique<EnemyChaseState>();
    }
    return nullptr;
}

void game::EnemyDeadState::OnEnter(dae::GameObject& owner)
{
    owner.SetLocalPosition({ -50.f, -50.f, 0.f });
}
