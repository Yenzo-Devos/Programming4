#pragma once
#include "ControllerDevice.h"
#include <memory>

namespace engine
{
	class GameObject;
}
namespace input
{
	class XController final : public ControllerDevice
	{
		class XControllerImpl;
		XControllerImpl* m_pImpl;
	
	public:
		XController(unsigned int controllerIdx);
		~XController();

		void PollInput() override;
		bool ValidateInput(ControllerInput input, InputType inputType) override;
	};
}


