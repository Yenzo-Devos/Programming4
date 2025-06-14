#include "RespawnComponent.h"
#include "GameObject.h"

game::RespawnComponent::RespawnComponent(dae::GameObject* pOwner, glm::vec2 respawnLocation)
	: BaseComponent(pOwner)
	, m_RespawnLocation{ respawnLocation }
{
}

void game::RespawnComponent::RespawnOwner()
{
	m_pOwner->SetLocalPosition(m_RespawnLocation);
}
