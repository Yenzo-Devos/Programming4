#pragma once
#include "Singleton.h"
#include "Command.h"
#include "GamePad.h"

#include <vector>
#include <memory>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput(float DeltaTime);
		void BindCommand(std::unique_ptr<Command> pCommand, int controllerID /*button and state)*/);
		void AddController();

	private:
		const int m_MaxNrOfGamePad{ 4 };

		std::vector<std::unique_ptr<Command>> m_pCommands{};
		std::vector<std::unique_ptr<GamePad>> m_pGamePads{};
	};

}
