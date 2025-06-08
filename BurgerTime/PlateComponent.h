#pragma once
#include "BaseComponent.h"
#include "Observer.h"
namespace game
{
	class PlateComponent : public dae::Observer, public dae::BaseComponent
	{
	public:
		PlateComponent(dae::GameObject* owner, int idGroup);
		virtual ~PlateComponent() = default;

		PlateComponent(const PlateComponent& other) = delete;
		PlateComponent(PlateComponent&& other) = delete;
		PlateComponent& operator=(const PlateComponent& other) = delete;
		PlateComponent& operator=(PlateComponent&& other) = delete;

		void Update(float) override {};
		void Broadcast(dae::GameObject* pGameObject, dae::Event event) override;
		
		int GetID() { return m_ID; }
	private:
		bool m_IsFull{ false };
		const int m_ID;
		void UpdateHitbox();
	};
}


