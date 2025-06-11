#include "IngredientFallingState.h"
#include "IngredientIdleState.h"
#include "IngredientOnPlateState.h"
#include "IngredientComponent.h"
#include "CollisionHandler.h"
#include "HitboxComponent.h"
#include "RenderComponent.h"
#include "FallComponent.h"
#include "EnemyComponent.h"

void game::IngredientFallingState::Update(float deltaTime)
{
    if (!m_GracePeriodOver)
    {
        m_AccuGraceTimer += deltaTime;
        if (m_AccuGraceTimer >= m_GraceTime)
            m_GracePeriodOver = true;
    }
}

std::unique_ptr<game::IngredientState> game::IngredientFallingState::HandleState(dae::GameObject& owner)
{
    if (!m_GracePeriodOver)
        return nullptr;

    EmptyLandingPlatform();

    auto pos = owner.GetWorldPosition();
    auto platformObj = dae::CollisionHandler::GetInstance().HasIngredientLanded({ pos.x, pos.y + 14 });
    if (!platformObj)
        return nullptr;

    if (platformObj->GetTag() == "platform")
    {
        for (int index{0}; index < 4; ++index)
            owner.GetComponent<dae::RenderComponent>()->ChangeOffset(index, index*16);
        return std::make_unique<IngredientIdleState>();
    }
    else if (platformObj->GetTag() == "plate")
    {
        for (int index{0}; index < 4; ++index)
            owner.GetComponent<dae::RenderComponent>()->ChangeOffset(index, index*16);
        return std::make_unique<IngredientOnPlateState>();
    }
    return nullptr;
}

void game::IngredientFallingState::OnEnter(dae::GameObject& owner)
{
    m_pHitboxComp = owner.GetComponent<dae::HitboxComponent>();
    owner.GetComponent<game::FallComponent>()->Activate(true);

    // check if enemies were on it and set them to falling
    std::vector<dae::GameObject*> enemyVec{};
    for (auto hitbox : m_pHitboxComp->GetAllHitboxes())
    {
        auto bufferVec = dae::CollisionHandler::GetInstance().IsOverlappingWithObject("enemy", hitbox);
        enemyVec.insert(enemyVec.end(), bufferVec.begin(), bufferVec.end());
    }
    for (auto enemy : enemyVec)
        enemy->GetComponent<EnemyComponent>()->StartFalling();
}

void game::IngredientFallingState::OnExit(dae::GameObject& owner)
{
    owner.GetComponent<game::FallComponent>()->Activate(false);
}

void game::IngredientFallingState::EmptyLandingPlatform()
{
    auto ingredientVec = dae::CollisionHandler::GetInstance().PerformIngredientCheck(m_pHitboxComp->GetHitbox("left_hitbox"));
    if (!ingredientVec.empty())
        for (const auto& ingredient : ingredientVec)
            for (int index{ 0 }; index < 4; ++index)
                ingredient.first->GetComponent<IngredientComponent>()->Hit(index);
}
