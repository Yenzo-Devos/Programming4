#include "IngredientFallingState.h"
#include "IngredientIdleState.h"
#include "IngredientOnPlateState.h"
#include "IngredientComponent.h"
#include "CollisionHandler.h"
#include "HitboxComponent.h"
#include "RenderComponent.h"
#include "FallComponent.h"

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

    EmptyLandingPlatform(owner);

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
    owner.GetComponent<game::FallComponent>()->Activate(true);
}

void game::IngredientFallingState::OnExit(dae::GameObject& owner)
{
    owner.GetComponent<game::FallComponent>()->Activate(false);
}

void game::IngredientFallingState::EmptyLandingPlatform(dae::GameObject& owner)
{
    auto hitbox = owner.GetComponent<dae::HitboxComponent>()->GetHitbox("left_hitbox");
    auto ingredientVec = dae::CollisionHandler::GetInstance().PerformIngredientCheck(hitbox);
    if (!ingredientVec.empty())
        for (const auto& ingredient : ingredientVec)
            for (int index{ 0 }; index < 4; ++index)
                ingredient.first->GetComponent<IngredientComponent>()->Hit(index);
}
