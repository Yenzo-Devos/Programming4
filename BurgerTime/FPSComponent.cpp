#include "FPSComponent.h"
#include "TextComponent.h"
#include <iomanip>
#include <sstream>

game::FPSComponent::FPSComponent(dae::GameObject* owner, dae::TextComponent* textComp)
	: BaseComponent(owner)
{
	m_pTextComp = textComp;
}

void game::FPSComponent::Update(float deltaTime)
{
	++m_Counter;
	m_AccuTime += deltaTime;

	if (m_AccuTime >= m_FPSRefreshRate)
	{
		float fps = m_Counter / m_AccuTime;
		m_AccuTime -= m_FPSRefreshRate;
		m_Counter = 0;

		if (fps == m_FPS)
			return;

		std::ostringstream ss;
		ss << std::fixed << std::setprecision(1) << fps << " FPS";
		m_pTextComp->SetText(ss.str());
		m_FPS = fps;
	}
	
}
