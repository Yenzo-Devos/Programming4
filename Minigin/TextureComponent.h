#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include <memory>

namespace dae
{
	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent(GameObject* owner, float x = 0, float y = 0);
		~TextureComponent() = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Render() override;
		void LoadTexture(const std::string& textureName);
	
	private:
		float m_X, m_Y;
		std::shared_ptr<Texture2D> m_pTexture;
	};
}