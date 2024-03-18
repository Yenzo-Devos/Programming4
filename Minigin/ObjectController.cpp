#include "ObjectController.h"

input::ObjectController::ObjectController(engine::GameObject* pControlledObject)
	: m_pControlledObject{ pControlledObject }
{
}

void input::ObjectController::SetInputMapping(std::shared_ptr<InputMapping>& inputMap)
{
	if (m_pInputMap)
		m_pInputMap.reset();

	m_pInputMap = inputMap;
}

void input::ObjectController::BindToController(unsigned int controllerIndex)
{
	m_pController = std::make_unique<input::XController>(controllerIndex);
}

void input::ObjectController::ProcessControllerInput()
{
	if (!m_pController)
		return;

	m_pInputMap->HandleControllerInput(m_pControlledObject, m_pController.get());
}

void input::ObjectController::ProcessKeyboardInput(SDL_Event& e)
{
	m_pInputMap->HandleKeyboardInput(m_pControlledObject, e);
}
