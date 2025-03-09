#pragma once
#include "Singleton.h"
#include "Command.h"
#include "GamePad.h"

#include <vector>
#include <memory>

namespace dae
{
	enum class InputState
	{
		Pressed,
		Released,
		Held
	};

	struct CommandInfo
	{
		std::unique_ptr<Command> pCommand;
		int controllerID;
		InputState state;
		GamePad::GamePadButton button;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput(float DeltaTime);
		void BindCommand(std::unique_ptr<Command> pCommand, int controllerID, InputState state, GamePad::GamePadButton button);
		void AddController();

	private:
		const int m_MaxNrOfGamePad{ 4 };

		std::vector<std::unique_ptr<CommandInfo>> m_pCommands{};
		std::vector<std::unique_ptr<GamePad>> m_pGamePads{};
	};

}
