#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(GameObject* owner, int maxHealth, TextureComponent* pTexture)
	: BaseComponent(owner)
	, Subject()
	, m_MaxHealth{ maxHealth }
	, m_CurrentHealth{ maxHealth }
	, m_pTexture{ pTexture }
{
}

void dae::HealthComponent::Update(float deltaTime)
{

}

void dae::HealthComponent::Render()
{

}
