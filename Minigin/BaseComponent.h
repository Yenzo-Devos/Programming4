#pragma once
#include <memory>

class GameObject;

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

	virtual void SetOwner(GameObject* ownerPtr);
	virtual void SetDead() { m_IsDead = true; }

protected:
	dae::GameObject* m_pOwner;

private:
	bool m_IsDead;
};

