#include "HitboxComponent.h"
#include <iostream>
#include <algorithm>

dae::HitboxComponent::HitboxComponent(GameObject* owner)
	: BaseComponent( owner )
{
}

void dae::HitboxComponent::AddHitbox(float halfWidth, float halfHeight)
{
	m_pHitboxVec.emplace_back(b2MakeBox(halfWidth, halfHeight));
}

std::vector<b2Polygon*> dae::HitboxComponent::GetAllHitboxes()
{
	std::vector<b2Polygon*> hitboxVec(m_pHitboxVec.size());
	std::transform(m_pHitboxVec.begin(), m_pHitboxVec.end(), std::back_inserter(hitboxVec), 
				   [](const std::unique_ptr<b2Polygon>& ptr) { return ptr.get(); });
	return hitboxVec;
}
