#pragma once
#include "BaseComponent.h"
#include "SpriteComponent.h"

namespace game
{
	class PointEffectComponent : public dae::BaseComponent
	{
	public:
		PointEffectComponent(dae::GameObject* owner, dae::SpriteComponent* spriteComp, float lifeTime);
		virtual ~PointEffectComponent() = default;

		PointEffectComponent(const PointEffectComponent& other) = delete;
		PointEffectComponent(PointEffectComponent&& other) = delete;
		PointEffectComponent& operator=(const PointEffectComponent& other) = delete;
		PointEffectComponent& operator=(PointEffectComponent&& other) = delete;

		void Update(float deltaTime) override;
		void SpawnEffect(glm::vec2 pos, int points);

	private:
		dae::SpriteComponent* m_pSpriteComp{};
		
		bool m_IsActive{ false };
		float m_AccuLifeTime{0.f};
		const float m_LifeTime{};
		void KillEffect();
	};
}