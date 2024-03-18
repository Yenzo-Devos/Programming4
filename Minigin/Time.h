#pragma once
#include "Singleton.h"
namespace engine
{
	class Time : public Singleton<Time>
	{
	public:
		Time() = default;
		virtual ~Time() = default;

		Time(const Time& other) = delete;
		Time(Time&& other) = delete;
		Time& operator=(const Time& other) = delete;
		Time& operator=(Time&& other) = delete;

		float GetDeltaTime() const { return m_DeltaTime; }
		void CalculateDeltaTime(auto currentTime, auto lastTime);
	private:
		float m_DeltaTime{};
	};
}


