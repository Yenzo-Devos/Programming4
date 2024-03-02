#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <string>

class TextureComponent final : public BaseComponent
{
public:
	TextureComponent(engine::GameObject* pOwner, std::string texture);
	~TextureComponent() = default;

	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) = delete;

	void Awake() override;
	void Render() const override;

private:
	std::shared_ptr<engine::Texture2D> m_pTexture;
};

