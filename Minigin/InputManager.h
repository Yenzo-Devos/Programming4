#pragma once
#include "Singleton.h"
#include "ObjectController.h"
#include "XController.h"
#include <vector>

namespace engine
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddObjectController(std::unique_ptr<input::ObjectController>& objectController);

	private:
		std::vector<std::unique_ptr<input::ObjectController>> m_pObjectControllers{};
		input::XController m_Controller{ 0 };
	};
}
