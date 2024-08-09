#pragma once
#include <memory>
#include "GameObject.h"

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
		virtual void Render() const = 0;

		virtual void SetDead() { m_IsDead = true; }
		virtual bool GetIsDead() { return m_IsDead; }
	protected:
		BaseComponent(dae::GameObject* pOwner);
		
		GameObject* GetOwner() const { return m_pOwner; }
	private:
		dae::GameObject* m_pOwner{ nullptr };
		bool m_IsDead{ false };
	};
}
