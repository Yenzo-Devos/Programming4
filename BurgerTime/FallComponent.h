#pragma once
#include "BaseComponent.h"
#include "glm.hpp"

namespace game
{
	class FallComponent : public dae::BaseComponent
	{
	public:
		FallComponent(dae::GameObject* pOwner, float fallingSpeed);
		~FallComponent() = default;

		FallComponent(const FallComponent& other) = delete;
		FallComponent(FallComponent&& other) = delete;
		FallComponent& operator=(const FallComponent& other) = delete;
		FallComponent& operator=(FallComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Activate(bool isActive) { m_IsActive = isActive; }

	private:
		bool m_IsActive{ false };
		const float m_Speed{};
		glm::vec3 m_Direction{ 0.f, 1.f, 0.f };
	};
}