#pragma once
#include "BaseComponent.h"
#include "glm.hpp"
namespace dae {
	class GameObject;
}

namespace game
{
	class RespawnComponent : public dae::BaseComponent
	{
	public:
		RespawnComponent(dae::GameObject* pOwner, glm::vec2 respawnLocation);
		~RespawnComponent() = default;

		RespawnComponent(const RespawnComponent& other) = delete;
		RespawnComponent(RespawnComponent&& other) = delete;
		RespawnComponent& operator=(const RespawnComponent& other) = delete;
		RespawnComponent& operator=(RespawnComponent&& other) = delete;

		void Update(float) override {}

		void RespawnOwner();
	private:
		glm::vec2 m_RespawnLocation;
	};
}


