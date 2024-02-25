#pragma once
#include "BaseComponent.h"
#include "Transform.h"

class RenderComponent : public BaseComponent
{
public:
	virtual void Awake() override;
	virtual void Render(const glm::mat4& viewProj) const = 0;

protected:
	dae::Transform* m_pTransform;
};

