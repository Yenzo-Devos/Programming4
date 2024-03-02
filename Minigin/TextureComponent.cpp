#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

TextureComponent::TextureComponent(dae::GameObject* pOwner, std::string texture)
	: BaseComponent(pOwner)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(texture);
}

void TextureComponent::Awake()
{
	
}

void TextureComponent::Render() const
{
	auto pos = GetOwner()->GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
