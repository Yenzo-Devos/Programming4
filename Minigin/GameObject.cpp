#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <functional>

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

void dae::GameObject::SetDead()
{
	m_IsDead = true;

	for (auto& child : m_pChildren)
	{
		child->SetParent(nullptr, false);
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

	auto lastValid = std::remove_if(std::begin(m_pChildren), std::end(m_pChildren),
		[&](GameObject* algChild) {
			return algChild == pChild;
		});
}

bool dae::GameObject::IsChild(GameObject* pParent)
{
	for (const auto& child : m_pChildren)
	{
		if (child == pParent)
			return true;

		if (child->IsChild(pParent))
			return true;
	}
	return false;
}

void dae::GameObject::SetPositionDirty()
{
	m_IsPositionDirty = true;
	std::for_each(m_pChildren.begin(), m_pChildren.end(), std::mem_fn(&dae::GameObject::SetPositionDirty));
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