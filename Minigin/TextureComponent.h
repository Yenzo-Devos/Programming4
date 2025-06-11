#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include <memory>

namespace dae
{
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(GameObject* owner, RenderComponent* pRenderComp);
		~TextureComponent() = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		virtual void Update(float) override {};
		void LoadTexture(const std::string& textureName);

		void RemoveLastRenderObject() {	m_pRenderComponent->RemoveLastRenderObject(); }
	
	private:
		RenderComponent* m_pRenderComponent;
		std::shared_ptr<Texture2D> m_pTexture;
	};
}