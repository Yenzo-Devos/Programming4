#include "TextureComponent.h"

dae::TextureComponent::TextureComponent(float x, float y)
	: BaseComponent()
	, m_X{ x }, m_Y{ y }
	, m_pTexture { nullptr }
{
}

void dae::TextureComponent::Render()
{
	if (m_pTexture)
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, m_X, m_Y);
}

void dae::TextureComponent::LoadTexture(const std::string& textureName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(textureName);
}
