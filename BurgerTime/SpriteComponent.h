#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

#include <memory>

namespace game
{
	struct Rect
	{
		int x;
		int y;
		int width;
		int height;
	};

	class SpriteComponent : public dae::BaseComponent
	{
	public:
		SpriteComponent(dae::GameObject* owner);
		~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() override;

		void LoadTexture(const std::string& textureName);
		void SetRow(int row) { }
		void SetAmountOfAnimFrames(int maxAnimFrames) { m_MaxAnimFrames = maxAnimFrames; }

	private:
		int m_Width{};
		int m_Height{};
		int m_CurrenCol{};
		int m_CurrentRow{};
		int m_MaxAnimFrames{};
		const int m_MaxRow{};

		Rect m_DstRect{};
		Rect m_SrcRect{};

		float m_AnimTime{};
		float m_AccuAnimTime{};
		
		std::unique_ptr<dae::Texture2D> m_pTexture;
	};
}



