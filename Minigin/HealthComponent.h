#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "TextureComponent.h"

namespace dae
{
	class HealthComponent : public BaseComponent, public Subject
	{
	public:
		HealthComponent(GameObject* owner, int maxHealth, TextureComponent* pTexture);
		virtual ~HealthComponent() = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		virtual void Update(float deltaTime) override;
		virtual void Render() override;
	private:
		const int m_MaxHealth;
		int m_CurrentHealth;

		TextureComponent* m_pTexture;
	};
}