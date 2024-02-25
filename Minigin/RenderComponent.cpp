#include "RenderComponent.h"

#include "GameObject.h"

void RenderComponent::Awake()
{
	m_pTransform = GetOwner()->GetComponent<dae::Transform>();

	assert(m_pTransform);
}
