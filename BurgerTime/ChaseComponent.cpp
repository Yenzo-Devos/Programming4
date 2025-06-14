#include "ChaseComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "CollisionHandler.h"
#include <vector>
#include "HitboxComponent.h"
#include "LivesComponent.h"

game::ChaseComponent::ChaseComponent(dae::GameObject* pOwner, std::vector<dae::GameObject*> pLadderVec, bool isBeingControlled)
	: BaseComponent(pOwner)
	, m_pLadderVec{ pLadderVec }
	, m_MoveLeftCommand{ std::make_unique<MoveCommand>(pOwner, 50.f, glm::vec2{-1.f, 0.f}) }
	, m_MoveRightCommand{ std::make_unique<MoveCommand>(pOwner, 50.f, glm::vec2{1.f, 0.f}) }
	, m_MoveUpCommand{ std::make_unique<MoveCommand>(pOwner, 25.f, glm::vec2{0.f, -1.f}) }
	, m_MoveDownCommand{ std::make_unique<MoveCommand>(pOwner, 25.f, glm::vec2{0.f, 1.f}) }
	, m_IsOwnerControlled{isBeingControlled}
{
}

void game::ChaseComponent::Update(float deltaTime)
{
	if (!m_IsActive)
	{
		if (m_IsOwnerControlled)
			CheckHitPlayer();
		return;
	}

	else if (m_IsActive && m_IsOwnerControlled)
	{
		Activate(false);
	}

	if (m_IsDirectionLocked)
	{
		m_AccuLockedDirTime += deltaTime;
		if (m_AccuLockedDirTime > m_LockedDirTime)
			m_IsDirectionLocked = false;
		else
		{
			MoveOnLockedPosition(deltaTime);
			return;
		}
	}
	
	if (!m_pLockedChaseObj)
		m_pLockedChaseObj = GetClosestObjectToChase();
	
	if (!m_IsOnLadder)
	{
		if (CheckLadderMovement(m_pLockedChaseObj, deltaTime))
			m_IsOnLadder = true;
		else
			MoveOnLockedPosition(deltaTime);
	}
	else
	{
		CheckMoveOnLadder(m_pLockedChaseObj, deltaTime);
	}

	CheckHitPlayer();
}

void game::ChaseComponent::AddObjectToChase(dae::GameObject* object)
{
	m_pObjectToChaseVec.emplace_back(object);
}

dae::GameObject* game::ChaseComponent::GetClosestObjectToChase()
{
	if (static_cast<int>(m_pObjectToChaseVec.size()) == 1)
		return m_pObjectToChaseVec[0];

	dae::GameObject* pTarget{};
	auto pos = m_pOwner->GetWorldPosition();
	float minDistSq = std::numeric_limits<float>::max();
	for (auto player : m_pObjectToChaseVec)
	{
		float dx = player->GetWorldPosition().x - pos.x;
		float dy = player->GetWorldPosition().x - pos.x;
		float distSq = dx * dx + dy * dy;

		if (distSq < minDistSq)
		{
			minDistSq = distSq;
			pTarget = player;
		}
	}
	return pTarget;
}

void game::ChaseComponent::CheckMoveOnLadder(dae::GameObject* pTarget, float deltaTime)
{
	// check what is closer x or y
	const auto pos = m_pOwner->GetWorldPosition();
	const auto targetPos = pTarget->GetWorldPosition();
	const auto deltaX = targetPos.x - pos.x;

	bool hasMoved{ false };
	if (deltaX > 0)
	{
		if (m_MoveRightCommand->Execute(deltaTime))
		{
			LockInDirection(glm::vec2{ 1.f, 0.f });
			hasMoved = true;
			m_IsOnLadder = false;
		}
	}
	else
	{
		if (m_MoveLeftCommand->Execute(deltaTime))
		{
			LockInDirection(glm::vec2{ -1.f, 0.f });
			hasMoved = true;
			m_IsOnLadder = false;
		}
	}

	if (!hasMoved)
	{
		if (CheckLadderMovement(pTarget, deltaTime))
			m_IsOnLadder = true;
		else
		{
			if (deltaX > 0 and m_MoveLeftCommand->Execute(deltaTime))
				LockInDirection(glm::vec2{ -1.f, 0.f });
			else if (deltaX <= 0 and m_MoveRightCommand->Execute(deltaTime))
				LockInDirection(glm::vec2{ 1.f, 0.f });
		
			m_IsOnLadder = false;
		}
	}
}

bool game::ChaseComponent::CheckLadderMovement(dae::GameObject* pTarget, float deltaTime)
{
	if (m_IsOnLadder)
	{
		MoveOnLockedPosition(deltaTime);
		return true;
	}

	if (m_pOwner->GetWorldPosition().y >= pTarget->GetWorldPosition().y)
	{
		if (m_MoveUpCommand->Execute(deltaTime))
		{
			LockInDirection(glm::vec2{ 0.f, -1.f });
			return true;
		}
		if (m_MoveDownCommand->Execute(deltaTime))
		{
			LockInDirection(glm::vec2{ 0.f, 1.f });
			return true;
		}
	}
	else if (m_pOwner->GetWorldPosition().y < pTarget->GetWorldPosition().y)
	{
		if (m_MoveDownCommand->Execute(deltaTime))
		{
			LockInDirection(glm::vec2{ 0.f, 1.f });
			return true;
		}
		if (m_MoveUpCommand->Execute(deltaTime))
		{
			LockInDirection(glm::vec2{ 0.f, -1.f });
			return true;
		}
	}
	return false;
}

void game::ChaseComponent::MoveOnLockedPosition(float deltaTime)
{
	if (m_LockedDirection.x == 1.f)
		m_MoveRightCommand->Execute(deltaTime);
	else if (m_LockedDirection.x == -1.f)
		m_MoveLeftCommand->Execute(deltaTime);
	else if (m_LockedDirection.y == 1.f)
		m_MoveDownCommand->Execute(deltaTime);
	else if (m_LockedDirection.y == -1.f)
		m_MoveUpCommand->Execute(deltaTime);
}

void game::ChaseComponent::LockInDirection(glm::vec2 dir)
{
	if (m_LockedDirection == dir)
		return;
	
	m_LockedDirection = dir;
	m_IsDirectionLocked = true;
	m_AccuLockedDirTime = 0.f;
	m_pLockedChaseObj = GetClosestObjectToChase();
}

void game::ChaseComponent::CheckHitPlayer()
{
	auto hitbox = m_pOwner->GetComponent<dae::HitboxComponent>();
	if (!game::CollisionHandler::GetInstance().IsOverlappingWithObject("player0", hitbox->GetHitbox("main_hitbox")).empty())
		dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByTag("player0")->GetComponent<LivesComponent>()->LoseLife(1);
	if (!game::CollisionHandler::GetInstance().IsOverlappingWithObject("player1", hitbox->GetHitbox("main_hitbox")).empty())
		dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByTag("player1")->GetComponent<LivesComponent>()->LoseLife(1);
}
