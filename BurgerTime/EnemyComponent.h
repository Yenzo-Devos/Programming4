#pragma once
#include "BaseComponent.h"
#include "EnemyState.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
}

namespace game
{
	class EnemyComponent : public dae::BaseComponent, public dae::Observer
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

		void StartFalling();
		void Hit();
		void Broadcast(dae::GameObject*, dae::Event event) override;

	private:
		std::unique_ptr<game::EnemyState> m_pState;
	};
}