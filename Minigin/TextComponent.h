#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Font.h"
#include "GameObject.h"
#include <string>

namespace engine
{
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(engine::GameObject* pOwner, const std::string& text = "nothing inserted", const std::string& font = "Lingua.otf", unsigned int fontSize = 36);
		~TextComponent() = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Awake() override;
		void Update() override;
		void Render() const override;
		void SetText(std::string newText);

	private:
		bool m_IsTextChanged;
		std::string m_Text;

		std::shared_ptr<engine::Font> m_Font;
		std::shared_ptr<engine::Texture2D> m_TextTexture;
	};
}
	

