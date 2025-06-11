#include "LivesDisplayComponent.h"
#include "LivesComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"

game::LivesDisplayComponent::LivesDisplayComponent(dae::GameObject* owner, dae::TextureComponent* pTexture)
	: BaseComponent(owner)
	, m_pLivesTexture{ pTexture }
{
}

void game::LivesDisplayComponent::Broadcast(dae::GameObject* pGameObject, dae::Event event)
{
	switch (event)
	{
	case dae::Event::OnPlayerDeath:
		if (pGameObject->GetComponent<game::LivesComponent>()->GetCurrentNrOfLives() >= 0)
			m_pLivesTexture->RemoveLastRenderObject();
		break;
	case dae::Event::OnPlayerScored:
		break;
	default:
		break;
	}
}
