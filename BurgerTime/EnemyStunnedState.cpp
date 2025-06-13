#include "EnemyStunnedState.h"
#include "EnemyChaseState.h"
#include "EnemyFallState.h"
#include "EnemySquishedState.h"
#include "ServiceLocator.h"

void game::EnemyStunnedState::Update(float deltaTime)
{
    m_AccuStunTime += deltaTime;
}

std::unique_ptr<game::EnemyState> game::EnemyStunnedState::HandleState(dae::GameObject&)
{
    if (m_GotHit)
        return std::make_unique<EnemySquishedState>(m_PointsToBeAwarded, m_pLastInteractedObj);

    if (m_IsFalling)
        return std::make_unique<EnemyFallState>(m_pLastInteractedObj, m_FirstToFall, m_NrOfEnemiesFalling);

    if (m_AccuStunTime >= m_StunTime)
        return std::make_unique<EnemyChaseState>();

    return nullptr;
}

void game::EnemyStunnedState::OnEnter(dae::GameObject& owner)
{
    owner.GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("sprayed");

    auto& ss = dae::ServiceLocator::GetSoundSystem();
    dae::AudioFile enemyFallAudio{ "../Data/sounds/Enemy_Sprayed.wav", "EnemySprayed", 0 };
    ss.AddToQueue(enemyFallAudio);
}

void game::EnemyStunnedState::Fall(dae::GameObject* pLastInteractedObj, bool isFirst, int nrOfEnemiesFalling)
{
    m_IsFalling = true;
    m_pLastInteractedObj = pLastInteractedObj;
    m_FirstToFall = isFirst;
    m_NrOfEnemiesFalling = nrOfEnemiesFalling;
}

void game::EnemyStunnedState::Hit(int points, dae::GameObject* pLastInteractedObj)
{
    m_GotHit = true;
    m_PointsToBeAwarded = points;
    m_pLastInteractedObj = pLastInteractedObj;
}
