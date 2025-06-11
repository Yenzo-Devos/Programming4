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
		EnemyComponent(dae::GameObject* pOwner, dae::GameObject* pointEffectObj, int pointMultiplier);
		~EnemyComponent() = default;

		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) = delete;

		void Update(float deltaTime) override;
		void HandleState();

		void StartFalling(dae::GameObject* pLastInteractedObj, bool isFirst, int nrOfEnemiesFalling);
		void Hit(dae::GameObject* pLastInteractedObj);
		void Broadcast(dae::GameObject*, dae::Event event) override;

		int GetPointMultiplier() const { return m_PointMultiplier; }
		dae::GameObject* GetPointEffect() const { return m_pPointEffectObj; }

	private:
		std::unique_ptr<game::EnemyState> m_pState;
		dae::GameObject* m_pPointEffectObj{};
		int m_PointMultiplier{};
	};
}