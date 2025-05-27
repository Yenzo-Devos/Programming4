#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::RenderComponent::RenderComponent(dae::GameObject* owner, bool srcRectEnabled)
	: BaseComponent( owner )
	, m_SourceRectEnabled{ srcRectEnabled }
{
}

void dae::RenderComponent::Render()
{
	SDL_Rect dstRect;
	dstRect.x = static_cast<int>(m_pOwner->GetWorldPosition().x);
	dstRect.y = static_cast<int>(m_pOwner->GetWorldPosition().y);
	dstRect.w = m_Width;
	dstRect.h = m_Heigth;

	SDL_Rect srcRect;
	srcRect.x = m_SrcRect.left;
	srcRect.y = m_SrcRect.bottom;
	srcRect.w = m_SrcRect.width;
	srcRect.h = m_SrcRect.height;

	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, dstRect, srcRect);
}

void dae::RenderComponent::SetTexture(Texture2D* pTexture, int width, int height)
{
	m_Width = width;
	m_Heigth = height;
	m_pTexture = std::make_shared<Texture2D>(pTexture);
}