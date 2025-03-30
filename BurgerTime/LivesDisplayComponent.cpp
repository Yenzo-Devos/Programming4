#include "LivesDisplayComponent.h"
#include "LivesComponent.h"
#include "GameObject.h"

dae::LivesDisplayComponent::LivesDisplayComponent(GameObject* owner, TextComponent* pText)
	: BaseComponent(owner)
	, m_pLivesText{pText}
{
	m_pLivesText->SetText("3 Lives");
}

void dae::LivesDisplayComponent::Broadcast(GameObject* pGameObject, Event event)
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

void dae::LivesDisplayComponent::UpdateLivesTexture(GameObject* pGameObject)
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
