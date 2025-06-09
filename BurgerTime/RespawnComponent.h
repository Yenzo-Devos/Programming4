#pragma once
#include "BaseComponent.h"
#include "glm.hpp"
namespace game {
	class GameObject;
}

class RespawnComponent : public dae::BaseComponent
{
public:
	RespawnComponent(dae::GameObject* pOwner, glm::vec3 respawnLocation);
	~RespawnComponent() = default;

	RespawnComponent(const RespawnComponent& other) = delete;
	RespawnComponent(RespawnComponent&& other) = delete;
	RespawnComponent& operator=(const RespawnComponent& other) = delete;
	RespawnComponent& operator=(RespawnComponent&& other) = delete;

	void RespawnOwner();
private:
	glm::vec3 m_RespawnLocation;
};

