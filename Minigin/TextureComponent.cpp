#include "TextureComponent.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent(GameObject* owner, RenderComponent* pRenderComp)
	: BaseComponent(owner)
	, m_pRenderComponent{ pRenderComp }
	, m_pTexture { nullptr }
{
}

void dae::TextureComponent::LoadTexture(const std::string& textureName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(textureName);
	m_pRenderComponent->SetTexture(m_pTexture.get());
}
