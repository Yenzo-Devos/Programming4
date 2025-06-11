#include "PointEffectComponent.h"
#include "GameObject.h"

game::PointEffectComponent::PointEffectComponent(dae::GameObject* owner, dae::SpriteComponent* spriteComp, float lifeTime)
	: BaseComponent( owner )
	, m_pSpriteComp{ spriteComp }
	, m_LifeTime{ lifeTime }
{
}

void game::PointEffectComponent::Update(float deltaTime)
{
	m_AccuLifeTime += deltaTime;
	if (m_AccuLifeTime > m_LifeTime)
		KillEffect();
}

void game::PointEffectComponent::SpawnEffect(glm::vec2 pos, int points)
{
	m_pSpriteComp->SetCurrentAnimation(std::to_string(points));
	m_pOwner->SetLocalPosition(glm::vec3{ pos.x, pos.y, 0.f });
}

void game::PointEffectComponent::KillEffect()
{
	m_pOwner->SetLocalPosition(glm::vec3{ -50.f, -50.f, 0.f });
	m_AccuLifeTime = 0.f;
	m_IsActive = false;
}
