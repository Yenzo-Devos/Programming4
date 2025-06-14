#pragma once
#include "Singleton.h"
#include "HitboxComponent.h"
#include "glm.hpp"
#include "GameObject.h"

namespace game
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
		
		bool IsNextWalkPossible(glm::vec2 pos, int width, int height);
		bool IsNextClimbPossible(glm::vec2 pos, int height);

		std::vector<dae::GameObject*> IsOverlappingWithObject(const std::string& identifier, glm::vec2 pos, int width, int height);
		std::vector<dae::GameObject*> IsOverlappingWithObject(const std::string& identifier, dae::HitboxComponent::Box* hitbox);

		std::vector<dae::GameObject*> AreEnemiesHit(dae::HitboxComponent::Box* hitbox);
		dae::GameObject* HasIngredientLanded(glm::vec2 pos);

		std::vector<std::pair<dae::GameObject*, int>> PerformIngredientCheck(dae::HitboxComponent::Box* hitbox);

	private:
		friend class Singleton<CollisionHandler>;
		CollisionHandler() = default;

		bool IsOverlapping(dae::HitboxComponent::Box& hitbox, dae::HitboxComponent::Box& otherHitbox) const;
		bool IsFullyOverlapping(dae::HitboxComponent::Box& hitbox, dae::HitboxComponent::Box& otherHitbox) const;

		std::vector<dae::GameObject*> m_pWalkableObjectVec{};
		std::vector<dae::GameObject*> m_pLadderVec{};
		std::vector<dae::GameObject*> m_pIngredientVec{};
		std::vector<dae::GameObject*> m_pEnemyVec{};
		std::vector<dae::GameObject*> m_pPlayerVec{};
		std::vector<dae::GameObject*> m_pPlatformVec{};
		std::vector<dae::GameObject*> m_pPlateVec{};
	};
}