#include "EnemySquishedState.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "EnemyDeadState.h"
#include "ServiceLocator.h"

game::EnemySquishedState::EnemySquishedState(int pointsToBeAwarded, dae::GameObject* pLastInteractedObj)
    : m_PointsToBeAwarded{ pointsToBeAwarded }
    , m_pLastInteractedObj{ pLastInteractedObj }
{
}

void game::EnemySquishedState::Update(float deltaTime)
{
    m_AccuAnimTime += deltaTime;
}

std::unique_ptr<game::EnemyState> game::EnemySquishedState::HandleState(dae::GameObject&)
{
    if (m_AccuAnimTime > m_AnimTime)
        return std::make_unique<EnemyDeadState>(m_PointsToBeAwarded, m_pLastInteractedObj);
    return nullptr;
}

void game::EnemySquishedState::OnEnter(dae::GameObject& owner)
{
    owner.GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("dying");

    auto& ss = dae::ServiceLocator::GetSoundSystem();
    dae::AudioFile enemyFallAudio{ "../Data/sounds/Enemy_Squashed.wav", "EnemySquashed", 0 };
    ss.AddToQueue(enemyFallAudio);
}
