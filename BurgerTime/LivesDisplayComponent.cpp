#include "LivesDisplayComponent.h"
#include "LivesComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

game::LivesDisplayComponent::LivesDisplayComponent(dae::GameObject* owner, dae::TextComponent* pText)
	: BaseComponent(owner)
	, m_pLivesText{pText}
{
	m_pLivesText->SetText("3 Lives");
}

void game::LivesDisplayComponent::Broadcast(dae::GameObject* pGameObject, dae::Event event)
{
	switch (event)
	{
	case dae::Event::OnPlayerDeath:
		UpdateLivesTexture(pGameObject);
		break;
	case dae::Event::OnPlayerScored:
		break;
	default:
		break;
	}
}

void game::LivesDisplayComponent::UpdateLivesTexture(dae::GameObject* pGameObject)
{
	//if (!pGameObject->HasComponent<LivesComponent>())
	//	return;

	int nrOfLives = pGameObject->GetComponent<game::LivesComponent>()->GetCurrentNrOfLives();
	m_LifeText = std::to_string(nrOfLives);
	if (nrOfLives == 1)
		m_LifeText += " Life";
	else
		m_LifeText += " Lives";

	m_pLivesText->SetText(m_LifeText);
}
