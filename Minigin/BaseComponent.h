#pragma once
#include <memory>

namespace engine
{
	class GameObject;
}

namespace engine
{
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Awake() = 0;
		virtual void Update() {};
		virtual void FixedUpdate(float) {};
		virtual void Render() const {};
		virtual void RenderUI() {};

		virtual void SetDead() { m_IsDead = true; }
		virtual bool GetIsDead() { return m_IsDead; }

	protected:
		BaseComponent(engine::GameObject* pOwner);
		engine::GameObject* GetOwner() const { return m_pOwner; }

	private:
		engine::GameObject* m_pOwner{ nullptr };
		bool m_IsDead{ false };
	};
}

