#pragma once
#include "BaseComponent.h"

class TextComponent;

class FPSComponent final : public BaseComponent
{
public:
	FPSComponent();
	virtual ~FPSComponent() = default;

	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;

	void Awake() override;
	void Update(float deltaTime) override;
	void Render() const override;

	void SetOwner(dae::GameObject* pOwner) override;

private:
	std::unique_ptr<TextComponent> m_pTextComponent;
	float m_FixedTimeStep{0.2f};
	float m_AccuFrameTime{};
};

