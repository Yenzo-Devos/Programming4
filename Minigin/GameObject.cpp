#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for (const auto& comp : m_ComponentVec)
	{
		comp->Update(deltaTime);
	}

	if (m_HasDeadComponent)
	{
		for (int index{}; index < static_cast<int>(m_ComponentVec.size()); ++index)
		{
			if (m_ComponentVec[index]->GetIsDead())
			{
				m_ComponentVec.erase(std::remove(m_ComponentVec.begin(), m_ComponentVec.end(), m_ComponentVec[index]), m_ComponentVec.end());
			}
		}
	}
}

void dae::GameObject::FixedUpdate(float fixedDeltaTime) { fixedDeltaTime; }

void dae::GameObject::Render() const
{
	for (const auto& comp : m_ComponentVec)
	{
		comp->Render();
	}
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPos)
{
	if (IsChild(pParent) or pParent == this or pParent == m_pParent)
		return;

	if (pParent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPos)
			// set local pos to world pos - parent world pos
			SetLocalPosition(GetWorldPosition() - m_pParent->GetWorldPosition());
		SetPositionDirty();
	}

	if (m_pParent)
		m_pParent->RemoveChild(this);
	
	m_pParent = pParent;
	
	if (m_pParent)
		m_pParent->AddChild(this);
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.emplace_back(pChild);
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	if (!pChild)
		return;

	std::remove_if(m_pChildren.begin(), m_pChildren.end(),
		[&](GameObject* child) {
			return child == pChild;
		});
}

bool dae::GameObject::IsChild(GameObject* pGameObject)
{
	return std::find_if(m_pChildren.begin(), m_pChildren.end(), pGameObject) != m_pChildren.end();
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_IsPositionDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_IsPositionDirty)
	{
		if (!m_pParent)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
	}
	m_IsPositionDirty = false;
}