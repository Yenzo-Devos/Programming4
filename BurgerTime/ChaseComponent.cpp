#include "ChaseComponent.h"
game::ChaseComponent::ChaseComponent(dae::GameObject* pOwner, std::vector<dae::GameObject*> pLadderVec)
	: BaseComponent(pOwner)
	, m_pLadderVec{ pLadderVec }
	, m_MoveLeftCommand{ std::make_unique<MoveCommand>(pOwner, 100.f, glm::vec3{-1.f, 0.f, 0.f}) }
	, m_MoveRightCommand{ std::make_unique<MoveCommand>(pOwner, 100.f, glm::vec3{1.f, 0.f, 0.f}) }
	, m_MoveUpCommand{ std::make_unique<MoveCommand>(pOwner, 100.f, glm::vec3{0.f, -1.f, 0.f}) }
	, m_MoveDownCommand{ std::make_unique<MoveCommand>(pOwner, 100.f, glm::vec3{0.f, 1.f, 0.f}) }
{
}

void game::ChaseComponent::Update(float deltaTime)
{
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

	dae::GameObject* pTarget = GetClosestObjectToChase();
	
	// check if there is a ladder?
	if (!m_IsOnLadder)
	{
		if (CheckLadderMovement(pTarget, deltaTime))
			m_IsOnLadder = true;
	}
	else
	{
		CheckMoveOnLadder(pTarget, deltaTime);
	}
}

void game::ChaseComponent::AddObjectToChase(dae::GameObject* object)
{
	m_pObjectToChaseVec.emplace_back(object);
}

dae::GameObject* game::ChaseComponent::GetClosestObjectToChase()
{
	dae::GameObject* pTarget{};
	auto pos = m_pOwner->GetWorldPosition();
	float minDistSq = std::numeric_limits<float>::max();
	for (auto player : m_pObjectToChaseVec)
	{
		float dx = player->GetWorldPosition().x - pos.x;
		float dy = player->GetWorldPosition().x - pos.x;
		float distSq = dx * dx + dy * dy;

		if (distSq < minDistSq);
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
	const auto deltaY = targetPos.y - pos.y;
	if (std::abs(deltaX) < std::abs(deltaY))
	{
		bool hasMoved{ false };
		if (deltaX > 0)
		{
			if (m_MoveRightCommand->Execute(deltaTime))
			{
				LockInDirection(glm::vec2{ 1.f, 0.f });
				hasMoved = true;
			}
		}
		else
		{
			if (m_MoveLeftCommand->Execute(deltaTime))
			{
				LockInDirection(glm::vec2{ -1.f, 0.f });
				hasMoved = true;
			}
		}

		if (!hasMoved)
		{
			if (CheckLadderMovement(pTarget, deltaTime))
				m_IsOnLadder = true;
			else
				if (deltaX > 0 and m_MoveLeftCommand->Execute(deltaTime))
					LockInDirection(glm::vec2{ -1.f, 0.f });
				else if (deltaX <= 0 and m_MoveRightCommand->Execute(deltaTime))
					LockInDirection(glm::vec2{ 1.f, 0.f });
		}
	}
	else
	{
		if (CheckLadderMovement(pTarget, deltaTime))
			m_IsOnLadder = true;
	}
}

bool game::ChaseComponent::CheckLadderMovement(dae::GameObject* pTarget, float deltaTime)
{
	if (m_pOwner->GetWorldPosition().y > pTarget->GetWorldPosition().y)
	{
		if (m_MoveUpCommand->Execute(deltaTime))
		{
			m_LockedDirection = glm::vec2{ 0.f, -1.f };
			return true;
		}
		if (m_MoveDownCommand->Execute(deltaTime))
		{
			m_LockedDirection = glm::vec2{ 0.f, 1.f };
			return true;
		}
	}
	else if (m_pOwner->GetWorldPosition().y < pTarget->GetWorldPosition().y)
	{
		if (m_MoveDownCommand->Execute(deltaTime))
		{
			m_LockedDirection = glm::vec2{ 0.f, 1.f };
			return true;
		}
		if (m_MoveUpCommand->Execute(deltaTime))
		{
			m_LockedDirection = glm::vec2{ 0.f, -1.f };
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
}
