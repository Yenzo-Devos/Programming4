#include "GameModeComponent.h"
#include "StartScreenState.h"
#include "PlayGameState.h"
#include "LeaderboardState.h"
#include "LeaderboardHandler.h"
#include "GameObject.h"
#include "CursorComponent.h"
#include "MenuComponent.h"
#include "ChaseComponent.h"
#include "PointsComponent.h"
#include "IngredientComponent.h"

game::GameModeComponent::GameModeComponent(dae::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_pState{ std::make_unique<StartScreenState>() }
{
}

void game::GameModeComponent::Update(float deltaTime)
{
	m_pState->Update(deltaTime);
	HandleState();

	if (m_LevelReloaded)
	{
		m_AccuReloadTime += deltaTime;
		if (m_AccuReloadTime > m_ReloadTime)
		{
			m_LevelReloaded = false;
			m_AccuReloadTime = 0.f;
		}
	}
}

void game::GameModeComponent::HandleState()
{
	auto newState = m_pState->HandleState(m_pOwner);
	if (newState != nullptr)
	{
		m_pState->OnExit(m_pOwner);
		m_pState = std::move(newState);
		m_pState->OnEnter(m_pOwner);
	}
}

void game::GameModeComponent::Broadcast(dae::GameObject* pGameObject, dae::Event event)
{
	switch (event)
	{
	case dae::Event::OnCursorClicked:
	{
		auto state = dynamic_cast<StartScreenState*>(m_pState.get());
		if (state)
			state->ModeSelected(pGameObject->GetComponent<MenuComponent>()->GetItemSelected());
		
		auto leaderboardState = dynamic_cast<LeaderboardState*>(m_pState.get());
		if (leaderboardState)
			LeaderboardHandler::GetInstance().ConfirmName();
		break;
	}
	case dae::Event::OnPlayerDeath:
	{
		std::vector<dae::GameObject*> pEnemies{};
		auto state = dynamic_cast<PlayGameState*>(m_pState.get());
		if (state)
		{
			pEnemies = dae::SceneManager::GetInstance().GetActiveScene()->GetAllObjectByTag("enemy");
			for (auto enemy : pEnemies)
				enemy->GetComponent<ChaseComponent>()->Activate(false);
		}
		break;
	}
	case dae::Event::OnGameEnded:
	{
		auto state = dynamic_cast<PlayGameState*>(m_pState.get());
		if (state)
		{
			m_FinishedPoints = pGameObject->GetComponent<PointsComponent>()->GetCurrentPoints();
			state->EndGame();
		}
		break;
	}
	case dae::Event::OnIngredientFallOnPlate:
	{
		if (pGameObject->GetComponent<IngredientComponent>()->IsTopBun())
		{
			int nrOfPlates = static_cast<int>(dae::SceneManager::GetInstance().GetActiveScene()->GetAllObjectByTag("plate").size());
			if (++m_NrOfBurgerDone == nrOfPlates)
			{
				auto state = dynamic_cast<PlayGameState*>(m_pState.get());
				if (state && !m_LevelReloaded)
				{
					m_LevelReloaded = state->LoadNextLevel(m_pOwner);
					state->SetObjectsDelete();
				}
			}
		}
		break;
	}
	default:
		break;
	}
}
