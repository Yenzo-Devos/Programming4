#pragma once

namespace dae
{
	class Controller final
	{
		class ControllerImpl;
		ControllerImpl* m_pImpl;

	public:
		explicit Controller(unsigned int controllerIndex);
		~Controller();
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		enum class ControllerInput
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			GamepadA = 0x1000,
			GamepadB = 0x2000,
			GamepadX = 0x4000,
			GamepadY = 0x8000
		};

		enum class InputType
		{
			IsDown,
			IsUp,
			Pressed
		};

		void PollInput();
		bool ValidateInput(ControllerInput input, InputType inputType);
		unsigned int GetIndex() const;
	};
}

