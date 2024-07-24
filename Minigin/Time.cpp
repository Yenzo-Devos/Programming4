#include "Time.h"
#include "chrono"

void dae::Time::CalculateDeltaTime(auto currentTime, auto lastTime)
{
	m_DeltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
}
