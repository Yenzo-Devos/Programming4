#pragma once
#include "Action.h"
#include "XController.h"
#include <SDL.h>
#include <vector>
#include <map>

namespace input
{
	class InputMapping
	{
	public:
		using controllerInputType = std::vector<std::pair<input::ControllerInput, input::InputType>>;

		InputMapping() = default;
		virtual ~InputMapping() = default;

		InputMapping(const InputMapping& other) = delete;
		InputMapping(InputMapping&& other) = delete;
		InputMapping& operator=(const InputMapping& other) = delete;
		InputMapping& operator=(InputMapping&& other) = delete;

		void BindActionToInput(std::unique_ptr<Action>& actionPtr, SDL_Scancode input);
		void BindActionToInput(std::unique_ptr<Action>& actionPtr,
			std::vector<SDL_Scancode> input);
		void BindActionToInput(std::unique_ptr<Action>& actionPtr,
			controllerInputType controllerInput,
			std::vector<SDL_Scancode> keyboardInput);
		void BindActionToInput(std::unique_ptr<Action>& actionPtr,
			controllerInputType controllerInput);

		void HandleControllerInput(engine::GameObject* gameObject, XController* controller);
		void HandleKeyboardInput(engine::GameObject* gameObject, SDL_Event& e);

	private:
		std::vector<std::tuple<std::unique_ptr<Action>, controllerInputType, std::vector<SDL_Scancode>>> m_InputMap{};
		//bool IsValid(SDL_Scancode input);
	};
}


