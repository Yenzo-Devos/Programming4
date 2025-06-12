#include "PepperComponent.h"
#include "SpriteComponent.h"
#include "CollisionHandler.h"
#include "EnemyComponent.h"

game::PepperComponent::PepperComponent(dae::GameObject* pOwner, dae::HitboxComponent* hitboxComp)
	: BaseComponent(pOwner)
	, m_pHitboxComp{ hitboxComp }
	, m_pPepperEvent{ std::make_unique<dae::Subject>() }
{
}

void game::PepperComponent::Update(float deltaTime)
{
	if (!m_IsActive)
		return;

	m_AccuActiveTime += deltaTime;
	if (m_AccuActiveTime >= m_ActiveTime)
		DeActivate();

	glm::vec2 pos = { m_pOwner->GetWorldPosition().x, m_pOwner->GetWorldPosition().y };
	auto enemies = dae::CollisionHandler::GetInstance().IsOverlappingWithObject("enemy", pos, m_pOwner->GetDimensions().first, m_pOwner->GetDimensions().second);
	if (enemies.empty())
		return;

	for (const auto& enemy : enemies)
		enemy->GetComponent<EnemyComponent>()->Broadcast(m_pOwner, dae::Event::EnemyStunned);
}

bool game::PepperComponent::Activate(glm::vec2 pos, glm::vec2 dir)
{
	if (m_IsActive)
		return false;

	if (m_PepperCount <= 0)
		return false;

	--m_PepperCount;
	m_pPepperEvent->Broadcast(m_pOwner, dae::Event::PepperUsed);

	m_IsActive = true;
	m_pOwner->SetLocalPosition({ pos, 0.f });
	if (dir.x == 1.f)
		m_pOwner->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("pepperRight");
	else if (dir.x == -1.f)
		m_pOwner->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("pepperLeft");
	return true;
}

void game::PepperComponent::AddObserver(dae::Observer* pObserver)
{
	m_pPepperEvent->AddObserver(pObserver);
}

void game::PepperComponent::RemoveObserver(dae::Observer* pObserver)
{
	m_pPepperEvent->RemoveObserver(pObserver);
}

void game::PepperComponent::DeActivate()
{
	m_IsActive = false;
	m_pOwner->SetLocalPosition({ -50.f, -50.f, 0.f });
	m_AccuActiveTime = 0.f;
}
