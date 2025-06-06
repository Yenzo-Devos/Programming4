#include "CollisionHandler.h"

bool dae::CollisionHandler::IsOverlapping(const HitboxComponent::Box& hitbox, const HitboxComponent::Box& otherHitbox) const
{
	if (hitbox.left > otherHitbox.left + otherHitbox.width or otherHitbox.left > hitbox.left + hitbox.width)
		return false;
	if (hitbox.top + hitbox.height > otherHitbox.top or otherHitbox.top + otherHitbox.height > hitbox.height)
		return false;
	return true;
}

bool dae::CollisionHandler::IsFullyOverlapping(const HitboxComponent::Box& hitbox, const HitboxComponent::Box& otherHitbox) const
{
	if (hitbox.left < otherHitbox.left or hitbox.left + hitbox.width > otherHitbox.left + otherHitbox.width)
		return false;
	if (hitbox.top < otherHitbox.top or hitbox.top + hitbox.height > otherHitbox.top + otherHitbox.height)
		return false;
	
	return false;
}
