#include "TextureComponent.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent(GameObject* owner)
	: BaseComponent(owner)
	, m_pTexture { nullptr }
{
}

void dae::TextureComponent::Render()
{
	if (m_pTexture)
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, m_pOwner->GetWorldPosition().x, m_pOwner->GetWorldPosition().y);
}

void dae::TextureComponent::LoadTexture(const std::string& textureName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(textureName);
}
