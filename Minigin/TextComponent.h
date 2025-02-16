#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <stdexcept>
#include <SDL_ttf.h>
#include <memory>
#include <string>
namespace dae
{
	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(float x = 0, float y = 0);
		virtual ~TextComponent() = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void SetText(const std::string& text);
		virtual void SetPosition(const float x, const float y);
		virtual void SetFont(const std::string& font, uint8_t fontSize);

	private:
		float m_X, m_Y;
		bool m_IsTextChanged;

		std::string m_Text{};
		std::shared_ptr<Font> m_pFont;
		std::unique_ptr<Texture2D> m_pTextTexture;
	};
}