#pragma once
#include "Singleton.h"
#include "Command.h"

#include <memory>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
		enum class keyState
		{
			IsDown,
			IsUp,
			IsPressed
		};
	public:
		bool ProcessInput();

		void BindAction(int controllerIndex, /*controller button*/, keyState keyState, std::unique_ptr<Command> pCommand);
		void BindAction(SDL_Scancode key, keyState keyState, std::unique_ptr<Command> pCommand);
	};

}
