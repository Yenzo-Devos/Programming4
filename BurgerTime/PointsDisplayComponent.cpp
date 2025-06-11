#include "PointsDisplayComponent.h"
#include "PointsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

game::PointsDisplayComponent::PointsDisplayComponent(dae::GameObject* owner, dae::TextComponent* ptext)
	: BaseComponent(owner)
	, m_pPointsText(ptext)
{
}

void game::PointsDisplayComponent::Broadcast(dae::GameObject* pGameObject, dae::Event event)
{
	switch (event)
	{
	case dae::Event::OnPlayerDeath:
		break;
	case dae::Event::OnPlayerScored:
	{
		int points = pGameObject->GetComponent<PointsComponent>()->GetCurrentPoints();
		m_pPointsText->SetText(std::to_string(points));
		break;
	}
	case dae::Event::OnIngredientFallOnPlate:
		break;
	case dae::Event::EnemyStunned:
		break;
	default:
		break;
	}
}