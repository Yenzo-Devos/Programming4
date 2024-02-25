#include "BaseComponent.h"

void BaseComponent::SetOwner(dae::GameObject* ownerPtr)
{
	m_pOwner = ownerPtr;
}
