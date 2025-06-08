#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

#include <iostream>

dae::SpriteComponent::SpriteComponent(dae::GameObject* owner, dae::RenderComponent* renderComp, int cellWidth, int cellHeight)
	: BaseComponent(owner)
	, m_pRenderComponent{ renderComp }
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
		if (m_AccuAnimTime > 1.f / m_CurrentAnimation.animationSpeed)
		{
			++m_CurrentFrame %= m_CurrentAnimation.frames;
			m_AccuAnimTime -= 1.f / m_CurrentAnimation.animationSpeed;

			dae::RenderComponent::Rect srcRect;
			srcRect.left = m_CurrentFrame * m_CellWidth;
			srcRect.bottom = m_CurrentAnimation.row * m_CellHeight;
			srcRect.width = m_CellWidth;
			srcRect.height = m_CellHeight;
			m_pRenderComponent->SetSourceRect(srcRect);
		}
	}
	else
	{
		dae::RenderComponent::Rect srcRect;
		srcRect.left = 0;
		srcRect.bottom = m_CurrentAnimation.row * m_CellHeight;
		srcRect.width = m_CellWidth;
		srcRect.height = m_CellHeight;
		m_pRenderComponent->SetSourceRect(srcRect);
	}
}

void dae::SpriteComponent::LoadTexture(const std::string& textureName)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(textureName);
	m_pRenderComponent->SetTexture(m_pTexture.get(), m_CellWidth, m_CellHeight);
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
	m_AccuAnimTime = 0.f;
}
