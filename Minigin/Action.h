#pragma once
#include "Command.h"
#include <memory>
namespace input
{
	class Action final
	{
	public:
		Action(std::unique_ptr<command::Command> command);
		virtual ~Action() = default;

		Action(const Action& other) = delete;
		Action(Action&& other) = delete;
		Action& operator=(const Action& other) = delete;
		Action& operator=(Action&& other) = delete;

		command::Command* GetCommand() { return m_pCommand.get(); }

	private:
		std::unique_ptr<command::Command> m_pCommand{};
	};
}


