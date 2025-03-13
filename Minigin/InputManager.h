#pragma once
#include "Singleton.h"
#include "Command.h"
#include "GamePad.h"
#include "KeyBoard.h"

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

	struct GamePadCommandInfo
	{
		std::unique_ptr<Command> pCommand;
		int gamePadID;
		InputState state;
		GamePad::GamePadButton button;
	};

	struct KeyBoardCommandInfo
	{
		std::unique_ptr<Command> pCommand;
		InputState state;
		SDL_Scancode key;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();

		bool ProcessInput(float DeltaTime);
		void BindCommand(std::unique_ptr<Command> pCommand, int controllerID, InputState state, GamePad::GamePadButton button);
		void BindCommand(std::unique_ptr<Command> pCommand, InputState state, SDL_Scancode key);
		void AddController();

	private:
		const int m_MaxNrOfGamePad{ 4 };

		std::vector<std::unique_ptr<GamePadCommandInfo>> m_pGamePadCommands{};
		std::vector<std::unique_ptr<KeyBoardCommandInfo>> m_pKeyBoardCommands{};
		std::vector<std::unique_ptr<GamePad>> m_pGamePads{};
		std::unique_ptr<KeyBoard> m_pKeyBoard;
	};

}
