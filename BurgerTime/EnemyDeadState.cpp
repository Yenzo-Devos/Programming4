#include "EnemyDeadState.h"
#include "GameObject.h"
#include "RespawnComponent.h"
#include "EnemyChaseState.h"
#include "PointsComponent.h"
#include "EnemyComponent.h"
#include "SpriteComponent.h"
#include "PointEffectComponent.h"

game::EnemyDeadState::EnemyDeadState(int pointsToBeAwarded, dae::GameObject* pLastInteractedObj)
    : m_PointsToBeAwarded{ pointsToBeAwarded }
    , m_pLastInteractedObj{ pLastInteractedObj }
{
}

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
    if (m_pLastInteractedObj)
    {
        m_pLastInteractedObj->GetComponent<PointsComponent>()->AddPoints(m_PointsToBeAwarded);
        auto pointEffect = owner.GetComponent<EnemyComponent>()->GetPointEffect();
        pointEffect->GetComponent<PointEffectComponent>()->SpawnEffect(owner.GetWorldPosition(), m_PointsToBeAwarded);
    }
    owner.SetLocalPosition({ -50.f, -50.f, 0.f });
}
