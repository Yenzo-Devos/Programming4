#include "EnemySquishedState.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "EnemyDeadState.h"

void game::EnemySquishedState::Update(float deltaTime)
{
    m_AccuAnimTime += deltaTime;
}

std::unique_ptr<game::EnemyState> game::EnemySquishedState::HandleState(dae::GameObject&)
{
    if (m_AccuAnimTime > m_AnimTime)
        return std::make_unique<EnemyDeadState>();
    return nullptr;
}

void game::EnemySquishedState::OnEnter(dae::GameObject& owner)
{
    owner.GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("dying");
}
