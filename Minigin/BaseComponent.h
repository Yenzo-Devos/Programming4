#pragma once
namespace dae
{
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(float deltaTime) { deltaTime; }
		virtual void Render() {};

		virtual void SetDead() { m_IsDead = true; }
		virtual bool GetIsDead() { return m_IsDead; }

	protected:
		BaseComponent() = default;

	private:
		bool m_IsDead = false;
	};
}

