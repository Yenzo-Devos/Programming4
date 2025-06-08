#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include <memory>

namespace dae
{
	class Observer;
}

namespace game
{
	class LivesComponent : public dae::BaseComponent
	{
	public:
		LivesComponent(dae::GameObject* owner, int maxHealth);
		virtual ~LivesComponent() = default;

		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;

		virtual void Update(float) override {};
		void LoseLife(int amount);
		
		void AddObserver(dae::Observer* pObserver);
		void RemoveObserver(dae::Observer* pObserver);

		int GetCurrentNrOfLives() const { return m_CurrentLives; }

	private:
		const int m_MaxLives;
		int m_CurrentLives;

		std::unique_ptr<dae::Subject> m_pPlayerDiedEvent;
	};
}

