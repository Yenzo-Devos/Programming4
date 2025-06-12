#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;
	class GameObject;
}

namespace game
{
	class PepperDisplayComponent : public dae::Observer, public dae::BaseComponent
	{
	public:
		PepperDisplayComponent(dae::GameObject* pOwner, dae::TextComponent* pText);
		virtual ~PepperDisplayComponent() = default;

		PepperDisplayComponent(const PepperDisplayComponent& other) = delete;
		PepperDisplayComponent(PepperDisplayComponent&& other) = delete;
		PepperDisplayComponent& operator=(const PepperDisplayComponent& other) = delete;
		PepperDisplayComponent& operator=(PepperDisplayComponent&& other) = delete;

		void Update(float) override {};
		void Broadcast(dae::GameObject* pGameObject, dae::Event event) override;

	private:
		dae::TextComponent* m_pPepperCountText{};
	};
}