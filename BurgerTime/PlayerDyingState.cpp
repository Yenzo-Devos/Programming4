#include "PlayerDyingState.h"
#include "SpriteComponent.h"
#include "PlayerIdleState.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RespawnComponent.h"
#include "ChaseComponent.h"

void game::PlayerDyingState::Update(float deltaTime)
{
	m_AccuDeadTime += deltaTime;
}

std::unique_ptr<game::PlayerState> game::PlayerDyingState::HandleState(PlayerComponent&)
{
	if (m_AccuDeadTime > m_DeadTime)
		return std::make_unique<PlayerIdleState>();
	
	return nullptr;
}

void game::PlayerDyingState::OnEnter(PlayerComponent& playerComp)
{
	playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("dying");
}

void game::PlayerDyingState::OnExit(PlayerComponent& playerComp)
{
	auto pEnemies = dae::SceneManager::GetInstance().GetActiveScene()->GetAllObjectByTag("enemy");
	for (auto enemy : pEnemies)
	{
		enemy->GetComponent<RespawnComponent>()->RespawnOwner();
		enemy->GetComponent<ChaseComponent>()->Activate(true);
	}
	playerComp.GetOwner()->GetComponent<RespawnComponent>()->RespawnOwner();
}