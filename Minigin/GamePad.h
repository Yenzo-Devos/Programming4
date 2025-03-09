#pragma once
#include <Windows.h>
namespace dae
{
	class GamePad
	{
		class GamePadImpl;
		GamePadImpl* m_pImpl;
	public:
		GamePad(int id);
		~GamePad();

		bool IsButtonDownThisFrame(unsigned int button) const;
		bool IsButtonUpThisFrame(unsigned int button) const;
		bool IsHeld(unsigned int button) const;

		enum class GamePadButton
		{
			DPAD_UP = 0x0001,
			DPAD_DOWN = 0x0002,
			DPAD_LEFT = 0x0004,
			DPAD_RIGHT = 0x0008,
			START = 0x0010,
			BACK = 0x0020,
			LEFT_THUMB = 0x0040,
			RIGHT_THUMB = 0x0080,
			LEFT_SHOULDER = 0x0100,
			RIGHT_SHOULDER = 0x0200,
			BUTTON_A = 0x1000,
			BUTTON_B = 0x2000,
			BUTTON_X = 0x4000,
			BUTTON_Y = 0x8000,
		};
	};
}

