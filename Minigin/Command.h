#pragma once
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	// create derived command for get an owned object by a controller
}

