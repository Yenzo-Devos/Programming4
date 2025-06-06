#include "HitboxComponent.h"
#include "GameObject.h"
#include <iostream>
#include <algorithm>

dae::HitboxComponent::HitboxComponent(GameObject* owner)
	: BaseComponent( owner )
{
}

void dae::HitboxComponent::AddHitbox(int left, int bottom, int width, int height)
{
	m_pHitboxVec.emplace_back(std::make_unique<Box>(left, bottom, width, height));
}

std::vector<dae::HitboxComponent::Box*> dae::HitboxComponent::GetAllHitboxes()
{
	std::vector<Box*> hitboxVec(m_pHitboxVec.size());
	std::transform(m_pHitboxVec.begin(), m_pHitboxVec.end(), std::back_inserter(hitboxVec), 
				   [](const std::unique_ptr<Box>& ptr) { return ptr.get(); });
	return hitboxVec;
}
