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

bool dae::CollisionHandler::IsNextWalkPossible(glm::vec2 pos, int width, int height)
{
	for (const auto& walkableObject : m_pWalkableObjectVec)
	{
		auto walkObjPos = walkableObject->GetWorldPosition();
		auto walkObjWidth = walkableObject->GetDimensions().first;
		if (pos.x > walkObjPos.x &&
			pos.x + width < walkObjPos.x + walkObjWidth &&
			std::abs((pos.y+height) - walkObjPos.y) <= 1.5f)
			return true;
	}
	return false;
}

bool dae::CollisionHandler::IsNextClimbPossible(glm::vec2 pos, int height)
{
	for (const auto& ladder : m_pLadderVec)
	{
		auto ladderPos = ladder->GetWorldPosition();
		auto ladderHeight = ladder->GetDimensions().second;
		if (std::abs(pos.x - ladderPos.x) <= 1.5f &&
			pos.y + height > ladderPos.y &&
			pos.y + height < ladderPos.y + ladderHeight)
			return true;
	}
	return false;
}

std::vector<dae::GameObject*> dae::CollisionHandler::IsOverlappingWithObject(const std::string& identifier, glm::vec2 pos, int width, int height)
{
	std::vector<dae::GameObject*> resultVec{};
	auto objectsToCheck = dae::SceneManager::GetInstance().GetActiveScene().GetAllObjectByTag(identifier);
	for (const auto& obj : objectsToCheck)
	{
		auto hitbox = obj->GetComponent<dae::HitboxComponent>()->GetHitbox("main_hitbox");
		HitboxComponent::Box pBox = HitboxComponent::Box{ static_cast<int>(pos.x), static_cast<int>(pos.y), width, height, 0, 0 };
		if (IsOverlapping(*hitbox, pBox))
			resultVec.emplace_back(obj);
	}
	return resultVec;
}

std::vector<dae::GameObject*> dae::CollisionHandler::IsOverlappingWithObject(const std::string& identifier, HitboxComponent::Box* hitbox)
{
	std::vector<dae::GameObject*> resultVec{};
	auto objectsToCheck = dae::SceneManager::GetInstance().GetActiveScene().GetAllObjectByTag(identifier);
	for (const auto& obj : objectsToCheck)
	{
		auto otherhitbox = obj->GetComponent<dae::HitboxComponent>()->GetHitbox("main_hitbox");
		if (IsOverlapping(*otherhitbox, *hitbox))
			resultVec.emplace_back(obj);
	}
	return resultVec;
}

std::vector<dae::GameObject*> dae::CollisionHandler::AreEnemiesHit(HitboxComponent::Box* hitbox)
{
	std::vector<dae::GameObject*> resultVec{};
	for (const auto& enemy : m_pEnemyVec)
	{
		auto enemyHitbox = enemy->GetComponent<dae::HitboxComponent>()->GetHitbox("main_hitbox");
		if (IsOverlapping(*hitbox, *enemyHitbox))
			resultVec.emplace_back(enemy);
	}
	return resultVec;
}

dae::GameObject* dae::CollisionHandler::HasIngredientLanded(glm::vec2 pos)
{
	for (const auto& platform : m_pPlatformVec)
	{		
		auto platformHitbox = platform->GetComponent<dae::HitboxComponent>()->GetHitbox("main_hitbox");
		if (std::abs((platformHitbox->top + platformHitbox->height) - pos.y) <= .5f and
			std::abs(platformHitbox->left - pos.x ) <= .5f)
			return platform;
	}
	for (const auto& plate : m_pPlateVec)
	{
		auto plateHitbox = plate->GetComponent<dae::HitboxComponent>()->GetHitbox("main_hitbox");
		if (std::abs((plateHitbox->top + 2) - pos.y) <= .5f and
			std::abs(plateHitbox->left - pos.x) <= 7.f)
			return plate;
	}
	return nullptr;
}

std::vector<std::pair<dae::GameObject*, int>> dae::CollisionHandler::PerformIngredientCheck(HitboxComponent::Box* hitbox)
{
	std::vector<std::pair<dae::GameObject*, int>> resultVec{};
	for (const auto& ingredient : m_pIngredientVec)
	{
		int count{ 0 };
		auto ingredientHitboxComp = ingredient->GetComponent<dae::HitboxComponent>();
		for (const auto& ingredientHitbox : ingredientHitboxComp->GetAllHitboxes())
		{
			if (IsOverlapping(*hitbox, *ingredientHitbox))
			{
				resultVec.emplace_back(std::make_pair(ingredient, count));
			}
			++count;
		}
	}
	return resultVec;
}

bool dae::CollisionHandler::IsOverlapping(HitboxComponent::Box& hitbox, HitboxComponent::Box& otherHitbox) const
{
	if (hitbox.left > otherHitbox.left + otherHitbox.width or otherHitbox.left > hitbox.left + hitbox.width)
		return false;
	if (hitbox.top + hitbox.height < otherHitbox.top or otherHitbox.top + otherHitbox.height < hitbox.top)
		return false;
	return true;
}

bool dae::CollisionHandler::IsFullyOverlapping(HitboxComponent::Box& hitbox, HitboxComponent::Box& otherHitbox) const
{
	if (hitbox.left < otherHitbox.left or hitbox.left + hitbox.width > otherHitbox.left + otherHitbox.width)
		return false;
	if (hitbox.top < otherHitbox.top or hitbox.top + hitbox.height > otherHitbox.top + otherHitbox.height)
		return false;
	
	return true;
}
