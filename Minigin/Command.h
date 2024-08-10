#pragma once

namespace dae
{
	class Command
	{
	public:
		Command();
		virtual ~Command();

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute() = 0;
	};
}


