#pragma once
#include "BaseComponent.h"
#include <memory>
namespace dae
{
	class TextComponent;
}

namespace game
{

	class FPSComponent final : public dae::BaseComponent
	{
	public:
		FPSComponent(dae::GameObject* owner, dae::TextComponent* textComp);
		~FPSComponent() = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Update(float deltaTime) override;

	private:
		dae::TextComponent* m_pTextComp;

		int m_Counter{ 0 };
		float m_FPS{ };
		float m_AccuTime{ 0.f };
		float m_FPSRefreshRate{ 1.f };
	};
}

