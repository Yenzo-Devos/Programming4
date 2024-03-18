#include "Time.h"
#include <chrono>

void engine::Time::CalculateDeltaTime(auto currentTime, auto lastTime)
{
	m_DeltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
}
