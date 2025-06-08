#include "PlateComponent.h"
#include "GameObject.h"
#include "HitboxComponent.h"

game::PlateComponent::PlateComponent(dae::GameObject* owner, int idGroup)
	: BaseComponent(owner)
	, m_ID{ idGroup }
{
}

void game::PlateComponent::Broadcast(dae::GameObject*, dae::Event event)
{
	switch (event)
	{
	case dae::Event::OnIngredientFallOnPlate:
		UpdateHitbox();
		break;
	}
}

void game::PlateComponent::UpdateHitbox()
{
	auto hitbox = m_pOwner->GetComponent<dae::HitboxComponent>();
	hitbox->MoveHitbox("main_hitbox", hitbox->GetHitbox("main_hitbox")->left, hitbox->GetHitbox("main_hitbox")->top - 16);
}
