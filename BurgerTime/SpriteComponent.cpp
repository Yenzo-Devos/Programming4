#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

#include <SDL.h>
#include <iostream>

game::SpriteComponent::SpriteComponent(dae::GameObject* owner, int cellWidth, int cellHeight, int maxCols, int animFrames)
	: BaseComponent(owner)
	, m_pTexture{ nullptr }
	, m_CellWidth{ cellWidth }
	, m_CellHeight{ cellHeight }
	, m_MaxCols{ maxCols }
	, m_MaxAnimFrames{ animFrames }
{
}

void game::SpriteComponent::Update(float deltaTime)
{
	// animation
	if (m_MaxAnimFrames > 1)
	{
		m_AccuAnimTime += deltaTime;
		if (m_AccuAnimTime > m_AnimTime)
		{
			++m_CurrentRow %= m_MaxAnimFrames;
			m_AccuAnimTime -= m_AnimTime;
		}
	}
}

void game::SpriteComponent::Render()
{
	if (!m_pTexture)
	{
		std::cerr << "no texture to render!" << '\n';
		return;
	}

	SDL_Rect dstRect;
	dstRect.x = static_cast<int>(m_pOwner->GetWorldPosition().x);
	dstRect.y = static_cast<int>(m_pOwner->GetWorldPosition().y);
	dstRect.w = m_CellWidth;
	dstRect.h = m_CellHeight;

	SDL_Rect srcRect;
	srcRect.x = m_CurrentRow * m_CellWidth;
	srcRect.y = m_CurrentCol * m_CellHeight;
	srcRect.w = m_CellWidth;
	srcRect.h = m_CellHeight;

	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, dstRect, srcRect);
}

void game::SpriteComponent::LoadTexture(const std::string& textureName)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(textureName);
}
