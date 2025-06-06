#include "PlayerPepperState.h"
#include "PlayerIdleState.h"
#include "SpriteComponent.h"

void game::PlayerPepperState::Update(float deltaTime)
{
	m_AccuTime += deltaTime;
	if (m_AccuTime > m_MaxPepperTime)
		m_TimerDone = true;
}

game::PlayerState* game::PlayerPepperState::HandleState(PlayerComponent&)
{
	if (m_TimerDone)
		return new PlayerIdleState();
	return nullptr;
}

void game::PlayerPepperState::OnEnter(PlayerComponent& playerComp)
{
	if (m_Direction.x == 1.f)
		playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("sprayRight");
	if (m_Direction.x == -1.f)
		playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("sprayLeft");
}

void game::PlayerPepperState::ChangeDirection(glm::vec3 direction)
{
	if (m_Direction != direction)
		m_Direction = direction;
}
