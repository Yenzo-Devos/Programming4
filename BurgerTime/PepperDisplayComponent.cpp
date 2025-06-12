#include "PepperDisplayComponent.h"
#include "TextComponent.h"
#include "PepperComponent.h"

game::PepperDisplayComponent::PepperDisplayComponent(dae::GameObject* pOwner, dae::TextComponent* pText)
	: BaseComponent(pOwner)
	, m_pPepperCountText{ pText }
{
}

void game::PepperDisplayComponent::Broadcast(dae::GameObject* pGameObject, dae::Event event)
{
	switch (event)
	{
	case dae::Event::PepperUsed:
	{
		m_pPepperCountText->SetText(std::to_string(pGameObject->GetComponent<game::PepperComponent>()->GetPepperCount()));
		break;
	}
	default:
		break;
	}
}
