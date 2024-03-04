#include "TextComponent.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Renderer.h"
#include <stdexcept>
#include <SDL_ttf.h>

engine::TextComponent::TextComponent(engine::GameObject* pOwner, const std::string& text, const std::string& font, unsigned int fontSize)
	: BaseComponent(pOwner)
	, m_Text{ text }
	, m_TextTexture{ nullptr }
	, m_IsTextChanged{ true }
{
	m_Font = engine::ResourceManager::GetInstance().LoadFont(font, fontSize);
}

void engine::TextComponent::Awake()
{

}

void engine::TextComponent::Update(float deltaTime)
{
	deltaTime;
	if (m_IsTextChanged)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(engine::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<engine::Texture2D>(texture);
		m_IsTextChanged = false;
	}
}

void engine::TextComponent::Render() const
{
	if (m_TextTexture)
	{
		auto pos{ GetOwner()->GetWorldPosition() };
		engine::Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

void engine::TextComponent::SetText(std::string newText)
{
	m_Text = newText;
	m_IsTextChanged = true;
}
