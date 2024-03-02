#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace engine
{
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(engine::GameObject* pOwner);
		virtual ~RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void Awake() override;
		virtual void Render(const glm::mat4& viewProj) const = 0;
	};
}

