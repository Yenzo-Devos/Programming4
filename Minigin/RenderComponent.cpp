#include "RenderComponent.h"

#include "GameObject.h"

void RenderComponent::Awake()
{
	m_pTransform = m_pOwner->GetComponent<dae::Transform>();

	assert(m_pTransform);
}
