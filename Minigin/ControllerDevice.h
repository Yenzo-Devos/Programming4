#pragma once
#include "Singleton.h"
namespace input
{
	enum class ControllerInput
	{
		faceUp,
		faceDown,
		faceLeft,
		faceRight,
		dPadUp,
		dPadDown,
		dPadLeft,
		dPadRight,
		joystickLeft,
		joystickRight,
		bumperLeft,
		bumperRight
	};
	enum class InputType
	{
		IsDown,
		IsUp,
		Pressed
	};

	class ControllerDevice abstract
	{
	public:
		virtual void PollInput() = 0;
		virtual bool ValidateInput(ControllerInput input, InputType inputType) = 0;
	};

}

