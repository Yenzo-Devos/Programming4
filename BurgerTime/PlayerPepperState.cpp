#include "PlayerPepperState.h"
#include "PlayerIdleState.h"
#include "SpriteComponent.h"
#include "ServiceLocator.h"

void game::PlayerPepperState::Update(float deltaTime)
{
	m_AccuTime += deltaTime;
	if (m_AccuTime > m_MaxPepperTime)
		m_TimerDone = true;
}

std::unique_ptr<game::PlayerState> game::PlayerPepperState::HandleState(PlayerComponent&)
{
	if (m_TimerDone)
		return std::make_unique<PlayerIdleState>();
	return nullptr;
}

void game::PlayerPepperState::OnEnter(PlayerComponent& playerComp)
{
	auto dir = playerComp.GetDirection();
	if (dir.x == 1.f)
		playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("sprayRight");
	if (dir.x == -1.f)
		playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("sprayLeft");

	auto& ss = dae::ServiceLocator::GetSoundSystem();
	dae::AudioFile pepperAudio{ "../Data/sounds/Pepper_Shake.wav", "PepperShake", 0 };
	ss.AddToQueue(pepperAudio);
}
