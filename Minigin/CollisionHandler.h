#pragma once
#include "Singleton.h"
#include "HitboxComponent.h"

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

		bool IsOverlapping(const HitboxComponent::Box& hitbox, const HitboxComponent::Box& otherHitbox);
	
	private:
		friend class Singleton<CollisionHandler>;
		CollisionHandler() = default;
	};
}