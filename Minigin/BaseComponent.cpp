#include "BaseComponent.h"

void BaseComponent::SetOwner(GameObject* ownerPtr)
{
	m_pOwner = ownerPtr;
}
