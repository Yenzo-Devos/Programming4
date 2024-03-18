#pragma once
#include "GameObject.h"

namespace command
{
	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;
		virtual void Execute(engine::GameObject* gameObject) = 0;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;
	};

	class MoveUp final : public Command
	{
	public:
		void Execute(engine::GameObject* gameObject) override;
	};

	class MoveDown final : public Command
	{
	public:
		void Execute(engine::GameObject* gameObject) override;
	};

	class MoveLeft final : public Command
	{
	public:
		void Execute(engine::GameObject* gameObject) override;
	};

	class MoveRight final : public Command
	{
	public:
		void Execute(engine::GameObject* gameObject) override;
	};
}


