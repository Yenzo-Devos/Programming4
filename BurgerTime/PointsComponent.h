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
	class PointsComponent : public dae::BaseComponent
	{
	public:
		PointsComponent(dae::GameObject* owner);
		virtual ~PointsComponent() = default;

		PointsComponent(const PointsComponent& other) = delete;
		PointsComponent(PointsComponent&& other) = delete;
		PointsComponent& operator=(const PointsComponent& other) = delete;
		PointsComponent& operator=(PointsComponent&& other) = delete;

		void Update(float) override {};

		void AddObserver(dae::Observer* pObserver);
		void RemoveObserver(dae::Observer* pObserver);

		void AddPoints(int amount);
		int GetCurrentPoints() const { return m_Points; }
	
	private:
		int m_Points{};

		std::unique_ptr<dae::Subject> m_pPointsScored;
	};
}