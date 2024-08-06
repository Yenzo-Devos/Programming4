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
	protected:
		BaseComponent(dae::GameObject* pOwner);
		
		dae::GameObject* m_pOwner;

	private:
		bool m_IsDead{ false };
	};
}
