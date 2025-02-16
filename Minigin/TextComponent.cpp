#include "TextComponent.h"

dae::TextComponent::TextComponent(float x, float y)
	: BaseComponent()
	, m_X{ x }, m_Y{ y }
	, m_Text{ "no text give" }
	, m_pTextTexture{ nullptr }
	, m_IsTextChanged{ true }
{
	m_pFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
}

void dae::TextComponent::Update(float deltaTime)
{
	deltaTime;
	if (m_IsTextChanged)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
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
		m_pTextTexture = std::make_unique<Texture2D>(texture);
		m_IsTextChanged = false;
	}
}

void dae::TextComponent::Render()
{
	if (m_pTextTexture != nullptr)
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, m_X, m_Y);
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_IsTextChanged = true;
}

void dae::TextComponent::SetPosition(const float x, const float y)
{
	m_X = x;
	m_Y = y;
}

void dae::TextComponent::SetFont(const std::string& font, uint8_t fontSize)
{
	m_pFont = dae::ResourceManager::GetInstance().LoadFont(font, fontSize);
}
