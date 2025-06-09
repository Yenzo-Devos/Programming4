#pragma once
#include "BaseComponent.h"
#include "EnemyState.h"

namespace dae
{
	class GameObject;
}

class EnemyComponent : public dae::BaseComponent
{
public:
	EnemyComponent(dae::GameObject* pOwner);
	~EnemyComponent() = default;

	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;

	void Update(float deltaTime) override;
	void HandleState();

private:
	std::unique_ptr<game::EnemyState> m_pState;
};

