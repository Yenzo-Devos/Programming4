#pragma once
#include "Singleton.h"
#include "Command.h"
#include "Controller.h"

#include <map>
#include <vector>
#include <memory>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput(float deltaTime);

		void AddController();
		void BindAction(int controllerIndex, Controller::ControllerInput controllerinput, Controller::InputType keyState, std::unique_ptr<Command> pCommand);
		void BindAction(SDL_Scancode button, std::unique_ptr<Command> pCommand);
		
	private:
		std::vector<std::unique_ptr<Controller>> m_pControllers{};
		int m_ControllerCounter{ 0 };
		
		// credit to Mathias Ooms for helping me setup the ControllerCommand and KeyboardCommand
		using ControllerInputIndex = std::pair<unsigned int, Controller::ControllerInput>;
		using ControllerState = std::pair<ControllerInputIndex, Controller::InputType>;
		using ControllerCommand = std::pair<ControllerState, std::unique_ptr<Command>>;

		using KeyboardCommand = std::pair<SDL_Scancode, std::unique_ptr<Command>>;

		std::vector<ControllerCommand> m_ControllerCommands{};
		std::vector<KeyboardCommand> m_KeyboardCommands{};
	};

}
