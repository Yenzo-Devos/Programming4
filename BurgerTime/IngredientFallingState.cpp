#include "IngredientFallingState.h"
#include "IngredientIdleState.h"
#include "IngredientOnPlateState.h"
#include "IngredientComponent.h"
#include "CollisionHandler.h"
#include "HitboxComponent.h"
#include "RenderComponent.h"
#include "FallComponent.h"
#include "EnemyComponent.h"
#include "PointsComponent.h"
#include "ServiceLocator.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlateComponent.h"


game::IngredientFallingState::IngredientFallingState(dae::GameObject* pLastInteractedObj)
    : m_pLastInteractedObj{ pLastInteractedObj }
{
}

void game::IngredientFallingState::Update(float deltaTime)
{
    if (!m_GracePeriodOver)
    {
        m_AccuGraceTimer += deltaTime;
        if (m_AccuGraceTimer >= m_GraceTime)
            m_GracePeriodOver = true;
    }
    for (auto enemy : CheckIfEnemiesCollide())
        enemy->GetComponent<EnemyComponent>()->Hit(m_pLastInteractedObj);
}

std::unique_ptr<game::IngredientState> game::IngredientFallingState::HandleState(dae::GameObject* owner)
{
    if (m_GracePeriodOver)
        EmptyLandingPlatform();

    auto pos = owner->GetWorldPosition();
    auto platformObj = game::CollisionHandler::GetInstance().HasIngredientLanded({ pos.x, pos.y + 14 });
    if (!platformObj)
        return nullptr;

    if (platformObj->GetTag() == "platform" and m_GracePeriodOver)
    {
        m_pLastInteractedObj->GetComponent<PointsComponent>()->AddPoints(50);
        for (int index{0}; index < 4; ++index)
            owner->GetComponent<dae::RenderComponent>()->ChangeOffset(index, index*16);
        return std::make_unique<IngredientIdleState>();
    }
    else if (platformObj->GetTag() == "plate")
    {
        m_pLastInteractedObj->GetComponent<PointsComponent>()->AddPoints(50);
        for (int index{0}; index < 4; ++index)
            owner->GetComponent<dae::RenderComponent>()->ChangeOffset(index, index*16);
        auto plate = GetCorrectPlate(owner);
        plate->GetComponent<PlateComponent>()->UpdateHitbox();
        return std::make_unique<IngredientOnPlateState>();
    }
    return nullptr;
}

void game::IngredientFallingState::OnEnter(dae::GameObject* owner)
{
    m_pHitboxComp = owner->GetComponent<dae::HitboxComponent>();
    owner->GetComponent<game::FallComponent>()->Activate(true);

    // check if enemies were on it and set them to falling
    auto enemySet = CheckIfEnemiesCollide();
    bool isFirst = true;
    for (auto enemy : enemySet)
    {
        if (isFirst)
        {
            enemy->GetComponent<EnemyComponent>()->StartFalling(m_pLastInteractedObj, isFirst, static_cast<int>(enemySet.size()));
            isFirst = false;
        }
        else
            enemy->GetComponent<EnemyComponent>()->StartFalling(m_pLastInteractedObj, isFirst, static_cast<int>(enemySet.size()));
    }

    auto& ss = dae::ServiceLocator::GetSoundSystem();
    dae::AudioFile ingredientFallAudio{ "../Data/sounds/Burger_Fall.wav", "BurgerFall", 0 };
    ss.AddToQueue(ingredientFallAudio);
}

void game::IngredientFallingState::OnExit(dae::GameObject* owner)
{
    owner->GetComponent<game::FallComponent>()->Activate(false);
}

void game::IngredientFallingState::EmptyLandingPlatform()
{
    auto ingredientVec = game::CollisionHandler::GetInstance().PerformIngredientCheck(m_pHitboxComp->GetHitbox("left_hitbox"));
    if (!ingredientVec.empty())
        for (const auto& ingredient : ingredientVec)
            for (int index{ 0 }; index < 4; ++index)
                ingredient.first->GetComponent<IngredientComponent>()->Hit(index, m_pLastInteractedObj);
}

std::unordered_set<dae::GameObject*> game::IngredientFallingState::CheckIfEnemiesCollide()
{
    std::unordered_set<dae::GameObject*> enemyVec{};
    for (auto hitbox : m_pHitboxComp->GetAllHitboxes())
    {
        auto bufferVec = game::CollisionHandler::GetInstance().IsOverlappingWithObject("enemy", hitbox);
        enemyVec.insert(bufferVec.begin(), bufferVec.end());
    }
    return enemyVec;
}

dae::GameObject* game::IngredientFallingState::GetCorrectPlate(dae::GameObject* pOwner)
{
    auto plates = dae::SceneManager::GetInstance().GetActiveScene()->GetAllObjectByTag("plate");
    for (auto plate : plates)
    {
        if (plate->GetComponent<PlateComponent>()->GetID() == pOwner->GetComponent<IngredientComponent>()->GetId())
            return plate;
    }
    return nullptr;
}
