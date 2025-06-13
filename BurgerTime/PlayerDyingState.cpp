#include "PlayerDyingState.h"
#include "SpriteComponent.h"
#include "PlayerIdleState.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RespawnComponent.h"
#include "ChaseComponent.h"
#include "ServiceLocator.h"

void game::PlayerDyingState::Update(float deltaTime)
{
	m_AccuDeadTime += deltaTime;
}

std::unique_ptr<game::PlayerState> game::PlayerDyingState::HandleState(dae::GameObject*)
{
	if (m_AccuDeadTime > m_DeadTime)
		return std::make_unique<PlayerIdleState>();
	
	return nullptr;
}

void game::PlayerDyingState::OnEnter(dae::GameObject* owner)
{
	owner->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("dying");
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	dae::AudioFile deathAudio{ "../Data/sounds/Death.wav", "Death", 0 };
	ss.AddToQueue(deathAudio);
	ss.StopMusic();
}

void game::PlayerDyingState::OnExit(dae::GameObject* owner)
{
	auto pEnemies = dae::SceneManager::GetInstance().GetActiveScene()->GetAllObjectByTag("enemy");
	for (auto enemy : pEnemies)
	{
		enemy->GetComponent<RespawnComponent>()->RespawnOwner();
		enemy->GetComponent<ChaseComponent>()->Activate(true);
	}
	owner->GetComponent<RespawnComponent>()->RespawnOwner();

	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.PlayMusic("../Data/sounds/BGM.wav", -1);
}