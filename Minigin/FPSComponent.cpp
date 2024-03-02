#include "FPSComponent.h"
#include "TextComponent.h"
#include <iomanip>
#include <sstream>

FPSComponent::FPSComponent(engine::GameObject* pOwner, TextComponent* textComponent)
	: BaseComponent(pOwner)
{
	m_pTextComponent = textComponent;
}

void FPSComponent::Awake()
{
}

void FPSComponent::Update(float deltaTime)
{
	m_AccuFrameTime += deltaTime;
	++m_DeltaTimeCount;
	if (m_AccuFrameTime > m_FixedTimeStep)
	{
		std::ostringstream ss;
		float fps = m_DeltaTimeCount / m_AccuFrameTime;
		if (fps == m_FPS)
			return;

		ss << std::fixed << std::setprecision(1) << fps << " FPS";
		m_pTextComponent->SetText(ss.str());
		m_AccuFrameTime -= m_FixedTimeStep;
		m_DeltaTimeCount = 0;
		m_FPS = fps;
	}
}
