#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

#include <memory>

namespace game
{
	class SpriteComponent : public dae::BaseComponent
	{
	public:
		SpriteComponent(dae::GameObject* owner, int cellWidth, int cellHeight, int maxCols, int animFrames);
		~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() override;

		void LoadTexture(const std::string& textureName);
		void SetCol(int col) { m_CurrentCol = col; }
		void SetAmountOfAnimFrames(int maxAnimFrames) { m_MaxAnimFrames = maxAnimFrames; }

	private:
		int m_CellWidth{};
		int m_CellHeight{};
		int m_CurrentCol{};
		int m_CurrentRow{};
		int m_MaxAnimFrames{};
		const int m_MaxCols{};

		float m_AnimTime{1.f};
		float m_AccuAnimTime{};
		
		std::shared_ptr<dae::Texture2D> m_pTexture;
	};
}



