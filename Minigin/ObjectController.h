#pragma once
#include "map"
#include "Action.h"
#include "Command.h"
#include "XController.h"
#include "InputMapping.h"

namespace engine
{
	class GameObject;
}
namespace input
{
	class ObjectController final
	{
	public:
		ObjectController(engine::GameObject* pControlledObject);
		virtual ~ObjectController() = default;

		ObjectController(const ObjectController& other) = delete;
		ObjectController(ObjectController&& other) = delete;
		ObjectController& operator=(const ObjectController& other) = delete;
		ObjectController& operator=(ObjectController&& other) = delete;

		void SetInputMapping(std::shared_ptr<InputMapping>& inputMap);
		void BindToController(unsigned int controllerIndex);
		void ProcessControllerInput();
		void ProcessKeyboardInput(SDL_Event& e);
		
	
	private:
		std::unique_ptr<input::XController> m_pController{};
		std::shared_ptr<InputMapping> m_pInputMap{};
		engine::GameObject* m_pControlledObject{};
	};
}

