#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

namespace dae
{
	class GamePad
	{
	public:
		bool IsButtonDownThisFrame(unsigned int button) const;
		bool IsButtonUpThisFrame(unsigned int button) const;
		bool IsHeld(unsigned int button) const;
	private:
		XINPUT_STATE m_CurrentState{};
		XINPUT_STATE m_PreviousState{};
		int m_ID;
	};
}

