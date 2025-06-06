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
	for (const auto& [key, value] : m_pHitboxMap)
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
	m_pHitboxMap[identifier] = std::make_unique<Box>(static_cast<int>(m_pOwner->GetWorldPosition().x) + offsetLeft,
													 static_cast<int>(m_pOwner->GetWorldPosition().y) + offsetTop,
													 width, height, offsetLeft, offsetTop);
}

dae::HitboxComponent::Box* dae::HitboxComponent::GetHitbox(const std::string& identifier)
{
	return m_pHitboxMap[identifier].get();
}