#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

#include <iostream>
#include <SDL.h>

dae::RenderComponent::RenderComponent(dae::GameObject* owner, bool srcRectEnabled)
	: BaseComponent( owner )
	, m_SourceRectEnabled{ srcRectEnabled }
{
}

void dae::RenderComponent::Render()
{
	if (!m_pTexture)
	{
		std::cerr << "no texture to render!" << '\n';
		return;
	}

	if (m_SourceRectEnabled)
	{
		SDL_Rect dstRect;
		dstRect.x = static_cast<int>(m_pOwner->GetWorldPosition().x);
		dstRect.y = static_cast<int>(m_pOwner->GetWorldPosition().y);
		dstRect.w = m_Width;
		dstRect.h = m_Height;

		SDL_Rect srcRect;
		srcRect.x = m_SrcRect.left;
		srcRect.y = m_SrcRect.bottom;
		srcRect.w = m_SrcRect.width;
		srcRect.h = m_SrcRect.height;

		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, dstRect, srcRect);
	}
	else if (m_Width == 0 && m_Height == 0)
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, m_pOwner->GetWorldPosition().x, m_pOwner->GetWorldPosition().y);
}

void dae::RenderComponent::SetTexture(Texture2D* pTexture, int width, int height)
{
	m_Width = width;
	m_Height = height;
	m_pTexture = pTexture;
}