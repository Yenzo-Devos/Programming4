#include "RespawnComponent.h"
#include "GameObject.h"

RespawnComponent::RespawnComponent(dae::GameObject* pOwner, glm::vec3 respawnLocation)
	: BaseComponent(pOwner)
	, m_RespawnLocation{ respawnLocation }
{
}

void RespawnComponent::RespawnOwner()
{
	m_pOwner->SetLocalPosition(m_RespawnLocation);
	// TODO: Set state to Moving again
}
