#include "Action.h"

input::Action::Action(std::unique_ptr<command::Command> command)
	: m_pCommand{ std::move(command) }
{
}
