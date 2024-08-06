#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <string>

namespace dae
{
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(GameObject* pOwner);
		~TextureComponent() = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Render() const override;
		void LoadTexture(const std::string& textureName);

	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}


