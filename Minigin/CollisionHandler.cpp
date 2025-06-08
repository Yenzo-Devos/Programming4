#include "CollisionHandler.h"
#include "SceneManager.h"
#include "Scene.h"
#include "HitboxComponent.h"

void dae::CollisionHandler::Init()
{
	m_pWalkableObjectVec = dae::SceneManager::GetInstance().GetActiveScene().GetAllObjectByTag("walkable_object");
	m_pLadderVec = dae::SceneManager::GetInstance().GetActiveScene().GetAllObjectByTag("ladder");
	m_pIngredientVec = dae::SceneManager::GetInstance().GetActiveScene().GetAllObjectByTag("ingredient");
	m_pPlatformVec = dae::SceneManager::GetInstance().GetActiveScene().GetAllObjectByTag("platform");
	m_pPlateVec = dae::SceneManager::GetInstance().GetActiveScene().GetAllObjectByTag("plate");
	m_pEnemyVec = dae::SceneManager::GetInstance().GetActiveScene().GetAllObjectByTag("enemy");
	// TODO: find a way to get player0 and 1 in this when needed
	m_pPlayerVec = dae::SceneManager::GetInstance().GetActiveScene().GetAllObjectByTag("player0");
}

bool dae::CollisionHandler::IsNextWalkPossible(HitboxComponent::Box* hitbox)
{
	for (const auto& walkableObject : m_pWalkableObjectVec)
	{
		auto walkHitbox = walkableObject->GetComponent<dae::HitboxComponent>()->GetHitbox("main_hitbox");
		if (IsFullyOverlapping(hitbox, walkHitbox))
			return true;
	}
	return false;
}

bool dae::CollisionHandler::IsNextClimbPossible(HitboxComponent::Box* hitbox)
{
	for (const auto& ladder : m_pLadderVec)
	{
		auto ladderHitbox = ladder->GetComponent<dae::HitboxComponent>()->GetHitbox("main_hitbox");
		if (IsOverlapping(hitbox, ladderHitbox) and
			std::abs(hitbox->left - static_cast<int>(ladder->GetWorldPosition().x)) <= .5f)
			return true;
	}
	return false;
}

std::pair<dae::GameObject*, int> dae::CollisionHandler::PerformIngredientCheck(HitboxComponent::Box* hitbox)
{
	for (const auto& ingredient : m_pIngredientVec)
	{
		// check if it's not falling

		int count{ 0 };
		auto ingredientHitboxComp = ingredient->GetComponent<dae::HitboxComponent>();
		for (const auto& ingredientHitbox : ingredientHitboxComp->GetAllHitboxes())
		{
			if (IsOverlapping(hitbox, ingredientHitbox))
			{
				return { ingredient, count };
			}
			++count;
		}
	}
	return { nullptr, -1 };
}

bool dae::CollisionHandler::IsOverlapping(HitboxComponent::Box* hitbox, HitboxComponent::Box* otherHitbox) const
{
	if (hitbox->left > otherHitbox->left + otherHitbox->width or otherHitbox->left > hitbox->left + hitbox->width)
		return false;
	if (hitbox->top + hitbox->height < otherHitbox->top or otherHitbox->top + otherHitbox->height < hitbox->top)
		return false;
	return true;
}

bool dae::CollisionHandler::IsFullyOverlapping(HitboxComponent::Box* hitbox, HitboxComponent::Box* otherHitbox) const
{
	if (hitbox->left < otherHitbox->left or hitbox->left + hitbox->width > otherHitbox->left + otherHitbox->width)
		return false;
	if (hitbox->top < otherHitbox->top or hitbox->top + hitbox->height > otherHitbox->top + otherHitbox->height)
		return false;
	
	return true;
}
