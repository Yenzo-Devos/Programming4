#include "EnemyShowPointsState.h"
#include "GameObject.h"
#include "RespawnComponent.h"
#include "EnemyChaseState.h"
#include "PointsComponent.h"
#include "EnemyComponent.h"
#include "PointEffectComponent.h"

game::EnemyShowPointsState::EnemyShowPointsState(int pointsToBeAwarded, dae::GameObject* pLastInteractedObj)
	: m_PointsToBeAwarded{ pointsToBeAwarded }
	, m_pLastInteractedObj{ pLastInteractedObj }
{
}

void game::EnemyShowPointsState::Update(float deltaTime)
{
	m_AccuShowTime += deltaTime;
}

std::unique_ptr<game::EnemyState> game::EnemyShowPointsState::HandleState(dae::GameObject&)
{
    if (m_AccuShowTime >= m_ShowPointsTime)
        return std::make_unique<EnemyChaseState>();

    return nullptr;
}

void game::EnemyShowPointsState::OnEnter(dae::GameObject& owner)
{
    if (m_pLastInteractedObj)
    {
        m_pLastInteractedObj->GetComponent<PointsComponent>()->AddPoints(m_PointsToBeAwarded);
        auto pointEffect = owner.GetComponent<EnemyComponent>()->GetPointEffect();
        pointEffect->GetComponent<PointEffectComponent>()->SpawnEffect(owner.GetWorldPosition(), m_PointsToBeAwarded);
    }
    m_BufferPos = owner.GetWorldPosition();
    owner.SetLocalPosition(glm::vec2{ -50.f, -50.f });
}

void game::EnemyShowPointsState::OnExit(dae::GameObject& owner)
{
    owner.SetLocalPosition(m_BufferPos);
}
