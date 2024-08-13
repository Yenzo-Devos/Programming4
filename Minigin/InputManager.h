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
	
		using ControllerKey = std::pair<unsigned int, Controller::ControllerInput>;
		using ControllerKeyState = std::pair<ControllerKey, Controller::InputType>;
		using ControllerCommand = std::pair<ControllerKeyState, std::unique_ptr<Command>>;

		using KeyboardCommand = std::pair<SDL_Scancode, std::unique_ptr<Command>>;

		std::vector<ControllerCommand> m_ConsoleCommands{};
		std::vector<KeyboardCommand> m_KeyboardCommands{};
	};

}
