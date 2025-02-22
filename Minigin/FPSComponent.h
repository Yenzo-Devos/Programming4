#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include <memory>

namespace dae
{
	class TextComponent;

	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent(GameObject* owner, TextComponent* textComp);
		~FPSComponent() = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Update(float deltaTime) override;

	private:
		TextComponent* m_pTextComp;

		int m_SampleSize{ 20 };
		int m_Counter{ 0 };
		float m_FPS{ };
		float m_AccuTime{ 0.f };
	};
}

