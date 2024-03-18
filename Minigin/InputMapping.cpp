#include "InputMapping.h"
#include "GameObject.h"
#include <SDL.h>

void input::InputMapping::BindActionToInput(std::unique_ptr<Action>& actionPtr, SDL_Scancode input)
{
	m_InputMap.push_back(std::make_tuple(std::move(actionPtr), controllerInputType{}, std::vector<SDL_Scancode>{input}));
}

void input::InputMapping::BindActionToInput(std::unique_ptr<Action>& actionPtr, std::vector<SDL_Scancode> input)
{
	m_InputMap.push_back(std::make_tuple(std::move(actionPtr), controllerInputType{}, input));
}

void input::InputMapping::BindActionToInput(std::unique_ptr<Action>& actionPtr, controllerInputType controllerInput, std::vector<SDL_Scancode> keyboardInput)
{
	m_InputMap.push_back(std::make_tuple(std::move(actionPtr), controllerInput, keyboardInput));
}

void input::InputMapping::BindActionToInput(std::unique_ptr<Action>& actionPtr, controllerInputType controllerInput)
{
	m_InputMap.push_back(std::make_tuple(std::move(actionPtr), controllerInput, std::vector<SDL_Scancode>{}));
}

void input::InputMapping::HandleControllerInput(engine::GameObject* gameObject, XController* controller)
{
	controller->PollInput();

	for (const auto& inputMap : m_InputMap)
	{
		for (const auto& controllerInput : std::get<1>(inputMap))
		{
			if (controller->ValidateInput(controllerInput.first, controllerInput.second))
			{
				std::get<0>(inputMap)->GetCommand()->Execute(gameObject);
				break;
			}
		}
	}
}

void input::InputMapping::HandleKeyboardInput(engine::GameObject* gameObject, SDL_Event& e)
{
	for (const auto& inputMap : m_InputMap)
	{
		for (const auto& keyboardInput : std::get<2>(inputMap))
		{
			if (keyboardInput == e.key.keysym.scancode)
			{
				std::get<0>(inputMap)->GetCommand()->Execute(gameObject);
			}
		}
	}
}


