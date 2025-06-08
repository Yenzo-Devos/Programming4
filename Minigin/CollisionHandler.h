#pragma once
#include "Singleton.h"
#include "HitboxComponent.h"
#include "glm.hpp"
#include "GameObject.h"

namespace dae
{
	class CollisionHandler final : public dae::Singleton<CollisionHandler>
	{
	public:
		~CollisionHandler() = default;

		CollisionHandler(const CollisionHandler& other) = delete;
		CollisionHandler(CollisionHandler&& other) = delete;
		CollisionHandler& operator=(const CollisionHandler& other) = delete;
		CollisionHandler& operator=(CollisionHandler&& other) = delete;

		void Init();
		
		bool IsNextWalkPossible(HitboxComponent::Box* hitbox);
		bool IsNextClimbPossible(HitboxComponent::Box* hitbox);

		std::vector<std::pair<GameObject*, int>> PerformIngredientCheck(HitboxComponent::Box* hitbox);

	private:
		friend class Singleton<CollisionHandler>;
		CollisionHandler() = default;

		bool IsOverlapping(HitboxComponent::Box* hitbox, HitboxComponent::Box* otherHitbox) const;
		bool IsFullyOverlapping(HitboxComponent::Box* hitbox, HitboxComponent::Box* otherHitbox) const;

		std::vector<GameObject*> m_pWalkableObjectVec{};
		std::vector<GameObject*> m_pLadderVec{};
		std::vector<GameObject*> m_pIngredientVec{};
		std::vector<GameObject*> m_pEnemyVec{};
		std::vector<GameObject*> m_pPlayerVec{};
		std::vector<GameObject*> m_pPlatformVec{};
		std::vector<GameObject*> m_pPlateVec{};
	};
}