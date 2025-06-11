#pragma once
#include "Observer.h"
#include "BaseComponent.h"

#include <string>

namespace dae
{
	class TextComponent;
	class GameObject;
}

namespace game
{
	class PointsDisplayComponent : public dae::Observer, public dae::BaseComponent
	{
	public:
		PointsDisplayComponent(dae::GameObject* owner, dae::TextComponent* ptext);
		virtual ~PointsDisplayComponent() = default;

		PointsDisplayComponent(const PointsDisplayComponent& other) = delete;
		PointsDisplayComponent(PointsDisplayComponent&& other) = delete;
		PointsDisplayComponent& operator=(const PointsDisplayComponent& other) = delete;
		PointsDisplayComponent& operator=(PointsDisplayComponent&& other) = delete;

		void Update(float) override {}
		void Broadcast(dae::GameObject* pGameObject, dae::Event event) override;
	private:
		dae::TextComponent* m_pPointsText;
	};
}