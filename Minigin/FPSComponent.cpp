#include "FPSComponent.h"
#include <iomanip>
#include <sstream>

dae::FPSComponent::FPSComponent(TextComponent* textComp)
	: BaseComponent()
{
	m_pTextComp = textComp;
}

void dae::FPSComponent::Update(float deltaTime)
{
	++m_Counter;
	m_AccuTime += deltaTime;
	if (m_Counter >= m_SampleSize)
	{
		float fps = m_Counter / m_AccuTime;
		m_Counter = 0;
		m_AccuTime = 0.f;
		if (fps == m_FPS)
			return;

		std::ostringstream ss;
		ss << std::fixed << std::setprecision(1) << fps << " FPS";
		m_pTextComp->SetText(ss.str());
		m_FPS = fps;
	}
	
}
