#include "BaseComponent.h"
#include "GameObject.h"
#include <stdexcept>
#include <string>

BaseComponent::BaseComponent(dae::GameObject* pOwner)
{
	if (!pOwner)
		throw std::runtime_error(std::string("owner is nullptr"));

	SetOwner(pOwner);
}

void BaseComponent::SetOwner(dae::GameObject* ownerPtr)
{
	m_pOwner = ownerPtr;
}
