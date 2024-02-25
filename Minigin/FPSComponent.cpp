#include "FPSComponent.h"
#include "TextComponent.h"
#include <iomanip>
#include <sstream>

FPSComponent::FPSComponent()
{
	m_pTextComponent = std::make_unique<TextComponent>();
}

void FPSComponent::Awake()
{
}

void FPSComponent::Update(float deltaTime)
{
	m_AccuFrameTime += deltaTime;
	if (m_AccuFrameTime > m_FixedTimeStep)
	{
		std::ostringstream ss;
		ss << std::fixed << std::setprecision(1) << 1.f / deltaTime << " FPS";
		m_pTextComponent->SetText(ss.str());
		m_pTextComponent->Update(deltaTime);
		m_AccuFrameTime -= m_FixedTimeStep;
	}
}

void FPSComponent::Render() const
{
	m_pTextComponent->Render();
}

void FPSComponent::SetOwner(dae::GameObject* pOwner)
{
	BaseComponent::SetOwner(pOwner);
	m_pTextComponent->SetOwner(pOwner);
}
