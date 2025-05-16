#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

#include <SDL.h>
#include <iostream>

dae::SpriteComponent::SpriteComponent(dae::GameObject* owner, int cellWidth, int cellHeight)
	: BaseComponent(owner)
	, m_pTexture{ nullptr }
	, m_CellWidth{ cellWidth }
	, m_CellHeight{ cellHeight }
{
}

void dae::SpriteComponent::Update(float deltaTime)
{
	// animation
	if (m_CurrentAnimation.frames > 1)
	{
		m_AccuAnimTime += deltaTime;
		if (m_AccuAnimTime > m_CurrentAnimation.animationSpeed)
		{
			++m_CurrentFrame %= m_CurrentAnimation.frames;
			m_AccuAnimTime -= m_CurrentAnimation.animationSpeed;
		}
	}
}

void dae::SpriteComponent::Render()
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
	srcRect.x = m_CurrentFrame * m_CellWidth;
	srcRect.y = m_CurrentAnimation.row * m_CellHeight;
	srcRect.w = m_CellWidth;
	srcRect.h = m_CellHeight;

	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, dstRect, srcRect);
}

void dae::SpriteComponent::LoadTexture(const std::string& textureName)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(textureName);
}

void dae::SpriteComponent::LoadAnimationData(const std::string& animName, int frames, int row, float animSpeed)
{
	m_AnimationMap[animName] = { frames, row, animSpeed };
}

void dae::SpriteComponent::SetCurrentAnimation(const std::string& animName)
{
	if (m_AnimationMap.empty())
	{
		std::cerr << "no animations loaded" << '\n';
		return;
	}
	
	m_CurrentAnimation = m_AnimationMap[animName];
	m_CurrentFrame = 0;
}
