#pragma once
#include "GameObject.h"

namespace command
{
	class Command
	{
	public:
		Command(engine::GameObject* gameObject) 
			: m_GameObject{ gameObject }
		{
		}

		virtual ~Command() = default;
		virtual void Execute() = 0;

	protected:
		engine::GameObject* GetControllerObject() const { return m_GameObject; }

	private:
		engine::GameObject* m_GameObject{ nullptr };
	};

	class MoveUp final : public Command
	{
	public:
		void Execute() override;

	private:
		glm::vec3 m_MoveDirection{ 0.f, -1.f, 0.f };
	};

	class MoveDown final : public Command
	{
	public:
		void Execute() override;

	private:
		glm::vec3 m_MoveDirection{ 0.f, 1.f, 0.f };
	};

	class MoveLeft final : public Command
	{
	public:
		void Execute() override;

	private:
		glm::vec3 m_MoveDirection{ -1.f, 0.f, 0.f };
	};

	class MoveRight final : public Command
	{
	public:
		void Execute() override;

	private:
		glm::vec3 m_MoveDirection{ 1.f, 0.f, 0.f };
	};
}


