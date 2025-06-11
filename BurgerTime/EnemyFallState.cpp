#include "EnemyFallState.h"
#include "GameObject.h"
#include "CollisionHandler.h"
#include "EnemyChaseState.h"
#include "EnemyDeadState.h"

void game::EnemyFallState::Update(float deltaTime)
{
	if (!m_GracePeriodOver)
	{
		m_AccuGraceTimer += deltaTime;
		if (m_AccuGraceTimer >= m_GraceTime)
			m_GracePeriodOver = true;
	}
}

std::unique_ptr<game::EnemyState> game::EnemyFallState::HandleState(dae::GameObject&)
{
	if (!m_GracePeriodOver)
		return nullptr;

	auto hitbox = m_pHitboxComp->GetHitbox("main_hitbox");
	auto platform = dae::CollisionHandler::GetInstance().IsOverlappingWithObject("platform", hitbox);
	if (static_cast<int>(platform.size()) > 0)
		return std::make_unique<EnemyChaseState>();
	
	auto plate = dae::CollisionHandler::GetInstance().IsOverlappingWithObject("plate", hitbox);
	if (static_cast<int>(plate.size()) > 0)
		return std::make_unique<EnemyDeadState>();
	
	return nullptr;
}

void game::EnemyFallState::OnEnter(dae::GameObject& owner)
{
	m_pHitboxComp = owner.GetComponent<dae::HitboxComponent>();
	m_pFallComp = owner.GetComponent<FallComponent>();
	m_pFallComp->Activate(true);
}

void game::EnemyFallState::OnExit(dae::GameObject&)
{
	m_pFallComp->Activate(false);
}
