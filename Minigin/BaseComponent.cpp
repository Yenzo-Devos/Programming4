#include "BaseComponent.h"
#include "GameObject.h"
#include <stdexcept>
#include <string>

engine::BaseComponent::BaseComponent(engine::GameObject* pOwner)
{
	if (!pOwner)
		throw std::runtime_error(std::string("owner is nullptr"));

	m_pOwner = pOwner;
}


