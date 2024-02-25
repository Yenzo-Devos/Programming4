#pragma once
//#include "GameObject.h"
#include <memory>

namespace dae
{
	class GameObject;
}

class BaseComponent
{
public:
	BaseComponent() = default;
	virtual ~BaseComponent() = default;

	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	virtual void Awake() = 0;
	virtual void Update(float) {};
	virtual void FixedUpdate(float) {};
	virtual void Render() const {};

	virtual void SetOwner(dae::GameObject* ownerPtr);
	virtual void SetDead() { m_IsDead = true; }
	virtual bool GetIsDead() { return m_IsDead; }

protected:
	dae::GameObject* GetOwner() const { return m_pOwner; }

private:
	dae::GameObject* m_pOwner{ nullptr };
	bool m_IsDead{ false };
};

