#include "EnemyFallState.h"
#include "GameObject.h"
#include "CollisionHandler.h"
#include "EnemyShowPointsState.h"
#include "EnemyDeadState.h"

game::EnemyFallState::EnemyFallState(dae::GameObject* pLastInteractedObj, bool isFirst, int nrOfEnemiesFalling)
	: m_pLastInteractedObj{ pLastInteractedObj }
	, m_FirstToFall{ isFirst }
	, m_NrOfEnemiesFalling{ nrOfEnemiesFalling }
{
}

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
		if (m_FirstToFall)
		{
			const int max = 6;
			int maxedCount = std::min(m_NrOfEnemiesFalling, max);
			int pointsResult = 500 * (1 << (maxedCount - 1));
			return std::make_unique<EnemyShowPointsState>(pointsResult, m_pLastInteractedObj);
		}
		else
			return std::make_unique<EnemyShowPointsState>();
	
	auto plate = dae::CollisionHandler::GetInstance().IsOverlappingWithObject("plate", hitbox);
	if (static_cast<int>(plate.size()) > 0)
		if (m_FirstToFall)
		{
			const int max = 6;
			int maxedCount = std::min(m_NrOfEnemiesFalling, max);
			int pointsResult = 500 * (1 << (maxedCount - 1));
			return std::make_unique<EnemyDeadState>(pointsResult, m_pLastInteractedObj);
		}
		else
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
