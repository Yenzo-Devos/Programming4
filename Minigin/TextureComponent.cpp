#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_pTexture{ nullptr }
{
}

void dae::TextureComponent::Render() const
{
	// render the text
	if (!m_pTexture)
		throw std::runtime_error(std::string("no texture to render"));

	glm::vec3 pos = m_pOwner->GetLocation();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void dae::TextureComponent::LoadTexture(const std::string& textureName)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(textureName);
}
