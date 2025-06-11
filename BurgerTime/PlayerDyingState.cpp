#include "PlayerDyingState.h"
#include "SpriteComponent.h"

std::unique_ptr<game::PlayerState> game::PlayerDyingState::HandleState(PlayerComponent&)
{
	// when the reset happened back to idle
	
	return nullptr;
}

void game::PlayerDyingState::OnEnter(PlayerComponent& playerComp)
{
	playerComp.GetOwner()->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("dying");
}
