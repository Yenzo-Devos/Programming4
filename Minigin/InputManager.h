#pragma once
#include "Singleton.h"

namespace engine
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
