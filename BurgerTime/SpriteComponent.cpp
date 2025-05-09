#include "SpriteComponent.h"

game::SpriteComponent::SpriteComponent(dae::GameObject* owner)
	: BaseComponent(owner)
	, m_pTexture{ nullptr }
{
}

void game::SpriteComponent::Update(float deltaTime)
{
}

void game::SpriteComponent::Render()
{
}

void game::SpriteComponent::LoadTexture(const std::string& textureName)
{
}
