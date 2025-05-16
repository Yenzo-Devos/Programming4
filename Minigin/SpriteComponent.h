#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

#include <unordered_map>
#include <memory>

namespace dae
{
	class SpriteComponent : public dae::BaseComponent
	{
		struct AnimationData
		{
			int frames;
			int row;
			float animationSpeed;
		};

	public:
		SpriteComponent(dae::GameObject* owner, int cellWidth, int cellHeight);
		~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() override;

		void LoadTexture(const std::string& textureName);

		void LoadAnimationData(const std::string& animName, int frames, int row, float animSpeed);
		void SetCurrentAnimation(const std::string& animName);

		// remove these for load data
		//void SetCol(int col) { m_CurrentCol = col; }
		//void SetAmountOfAnimFrames(int maxAnimFrames) { m_MaxAnimFrames = maxAnimFrames; }

	private:
		int m_CellWidth{};
		int m_CellHeight{};
		int m_CurrentFrame{};
		float m_AccuAnimTime{};
		
		AnimationData m_CurrentAnimation{};
		std::unordered_map<std::string, AnimationData> m_AnimationMap;
		std::shared_ptr<dae::Texture2D> m_pTexture;
	};
}



