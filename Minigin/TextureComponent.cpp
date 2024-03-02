#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

TextureComponent::TextureComponent(engine::GameObject* pOwner, std::string texture)
	: BaseComponent(pOwner)
{
	m_pTexture = engine::ResourceManager::GetInstance().LoadTexture(texture);
}

void TextureComponent::Awake()
{
	
}

void TextureComponent::Render() const
{
	auto pos = GetOwner()->GetPosition();
	engine::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
