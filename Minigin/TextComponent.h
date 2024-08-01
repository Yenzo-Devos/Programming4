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
		~TextComponent() override = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;
		void SetText(std::string newText);
		void SetFont(std::shared_ptr<dae::Font> font);

	private:
		bool m_IsTextChanged;
		std::string m_Text;
		std::shared_ptr<dae::Font> m_Font;
		std::unique_ptr<dae::Texture2D> m_TextTexture;
	};
}


