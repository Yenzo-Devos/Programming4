#include "CollisionHandler.h"

bool dae::CollisionHandler::IsOverlapping(const HitboxComponent::Box& hitbox, const HitboxComponent::Box& otherHitbox)
{
	if (hitbox.left > otherHitbox.left + otherHitbox.width or otherHitbox.left > hitbox.left + hitbox.width)
		return false;
	if (hitbox.top + hitbox.height > otherHitbox.top or otherHitbox.top + otherHitbox.height > hitbox.height)
		return false;
	return true;
}
