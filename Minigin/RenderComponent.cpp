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
		for (const RenderObject& obj : m_ObjectToRender)
		{
			SDL_Rect dstRect;
			dstRect.x = static_cast<int>(m_pOwner->GetWorldPosition().x) + obj.offsetX;
			dstRect.y = static_cast<int>(m_pOwner->GetWorldPosition().y) + obj.offsetY;
			dstRect.w = obj.dstRect.width;
			dstRect.h = obj.dstRect.height;

			SDL_Rect srcRect;
			srcRect.x = obj.srcRect.left;
			srcRect.y = obj.srcRect.bottom;
			srcRect.w = obj.srcRect.width;
			srcRect.h = obj.srcRect.height;
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, dstRect, srcRect);
		}
	}
	else
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, m_pOwner->GetWorldPosition().x, m_pOwner->GetWorldPosition().y);
}

void dae::RenderComponent::SetTexture(Texture2D* pTexture)
{
	m_pTexture = pTexture;
}

void dae::RenderComponent::AddObjectToRender(const Rect& dstRect, const Rect& srcRect, int offsetX, int offsetY)
{
	m_ObjectToRender.emplace_back(RenderObject{dstRect, srcRect, offsetX, offsetY});
}
