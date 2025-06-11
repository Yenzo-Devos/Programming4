#include "EnemyChaseState.h"
#include "EnemyStunnedState.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "EnemyFallState.h"
#include "EnemySquishedState.h"

game::EnemyChaseState::EnemyChaseState(dae::SpriteComponent* spriteComp, ChaseComponent* chaseComp)
	: m_pSpriteComp{ spriteComp }
	, m_pChaseComp{ chaseComp }
{
}

void game::EnemyChaseState::Update(float)
{
	ChangeAnimation(m_pChaseComp->GetDirection());
}

std::unique_ptr<game::EnemyState> game::EnemyChaseState::HandleState(dae::GameObject&)
{
	if (m_IsStunned)
		return std::make_unique<EnemyStunnedState>();
	if (m_GotHit)
		return std::make_unique<EnemySquishedState>();
	if (m_IsFalling)
		return std::make_unique<EnemyFallState>();

	return nullptr;
}

void game::EnemyChaseState::OnEnter(dae::GameObject& owner)
{
	m_pSpriteComp = owner.GetComponent<dae::SpriteComponent>();
	m_pChaseComp = owner.GetComponent<ChaseComponent>();
	m_pChaseComp->Activate(true);
}

void game::EnemyChaseState::OnExit(dae::GameObject&)
{
	m_pChaseComp->Activate(false);
}

void game::EnemyChaseState::ChangeAnimation(glm::vec2 dir)
{
	if (m_Direction == dir)
		return;

	m_Direction = dir;
	if (m_Direction.x == 1.f)
		m_pSpriteComp->SetCurrentAnimation("walkRight");
	if (m_Direction.x == -1.f)
		m_pSpriteComp->SetCurrentAnimation("walkLeft");
	if (m_Direction.y == 1.f)
		m_pSpriteComp->SetCurrentAnimation("walkDown");
	if (m_Direction.y == -1.f)
		m_pSpriteComp->SetCurrentAnimation("walkUp");
}
