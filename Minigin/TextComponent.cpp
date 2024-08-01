#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "ResourceManager.h"

#include <stdexcept>
#include <SDL_ttf.h>

dae::TextComponent::TextComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_Text{ "no text given" }
	, m_Font{ nullptr }
	, m_TextTexture{ nullptr }
	, m_IsTextChanged{ true }
{
	
}

void dae::TextComponent::Update(float deltaTime)
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
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_unique<Texture2D>(texture);
		m_IsTextChanged = false;
	}
}

void dae::TextComponent::Render() const
{
	// render the text
	if (!m_TextTexture)
		throw std::runtime_error(std::string("no texture to render"));

	// if you have parent get location
	auto pos{ m_pOwner->GetLocation() };
	dae::Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
}

void dae::TextComponent::SetText(std::string newText)
{
	m_Text = newText;
	m_IsTextChanged = true;
}

void dae::TextComponent::SetFont(std::shared_ptr<dae::Font> font)
{
	m_Font = std::move(font);
}
