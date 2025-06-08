#include "HitboxComponent.h"
#include "GameObject.h"
#include <iostream>
#include <algorithm>

dae::HitboxComponent::HitboxComponent(GameObject* owner)
	: BaseComponent( owner )
{
}

void dae::HitboxComponent::UpdateHitboxPosition()
{
	for (const auto& [key, value] : m_pHitboxVec)
	{
		if (value)
		{
			value->left = static_cast<int>(m_pOwner->GetWorldPosition().x) + value->offsetLeft;
			value->top = static_cast<int>(m_pOwner->GetWorldPosition().y) + value->offsetTop;
		}
	}
}

void dae::HitboxComponent::AddHitbox(const std::string& identifier, int offsetLeft, int offsetTop, int width, int height)
{
	m_pHitboxVec.emplace_back(std::make_pair(identifier, std::make_unique<Box>(static_cast<int>(m_pOwner->GetWorldPosition().x) + offsetLeft,
													static_cast<int>(m_pOwner->GetWorldPosition().y) + offsetTop,
													width, height, offsetLeft, offsetTop)));
}

dae::HitboxComponent::Box* dae::HitboxComponent::GetHitbox(const std::string& identifier)
{
	auto it = std::find_if(m_pHitboxVec.begin(), m_pHitboxVec.end(),
		[&identifier](const auto& pair) {
			return pair.first == identifier;
		});
	
	return (it != m_pHitboxVec.end()) ? it->second.get() : nullptr;
}

std::vector<dae::HitboxComponent::Box*> dae::HitboxComponent::GetAllHitboxes()
{
	std::vector<Box*> ptrs{};
	std::transform(m_pHitboxVec.begin(), m_pHitboxVec.end(), std::back_inserter(ptrs),
				   [](const auto& pair) 
				   { return pair.second.get(); });
	return ptrs;
}
