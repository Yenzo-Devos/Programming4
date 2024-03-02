#pragma once
#include "BaseComponent.h"


namespace engine
{
	class TextComponent;

	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(engine::GameObject* pOwner, TextComponent* textComponent);
		virtual ~FPSComponent() = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Awake() override;
		void Update(float deltaTime) override;

	private:
		TextComponent* m_pTextComponent;
		float m_FixedTimeStep{ 0.2f };
		float m_AccuFrameTime{};
		float m_FPS{};
		int m_DeltaTimeCount{};
	};
}


