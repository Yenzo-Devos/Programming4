#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include <string>

namespace dae
{
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject* pOwner);
		~TextComponent() = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;
		void SetText(std::string newText);
		void SetFont(std::string fontName, int fontSize);

	private:
		bool m_IsTextChanged;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::unique_ptr<Texture2D> m_TextTexture;
	};
}


