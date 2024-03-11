#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"

#include <stdexcept>
#include <string>

engine::GameObject::~GameObject() = default;

void engine::GameObject::Update(float deltaTime)
{
	for (const std::unique_ptr<BaseComponent>& component : m_pComponentVector)
	{
		if (!component)
			continue;

		component->Update(deltaTime);
	}
}

void engine::GameObject::FixedUpdate(float fixedDeltaTime)
{
	fixedDeltaTime;
}

void engine::GameObject::Render() const
{
	for (const std::unique_ptr<BaseComponent>& component : m_pComponentVector)
	{
		if (!component)
			continue;

		component->Render();
		component->RenderUI();
	}
}

void engine::GameObject::RemoveDeadComponents()
{
	for (int componentIndex{ 0 }; componentIndex < m_pComponentVector.size(); ++componentIndex)
	{
		if (m_pComponentVector[componentIndex].get()->GetIsDead())
			m_pComponentVector[componentIndex].reset();
	}
}

void engine::GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	if (pParent == this || IsChild(pParent) || m_pParent == pParent)
		return;

	if (!pParent)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - pParent->GetWorldPosition());
		SetPositionDirty();
	}

	if (m_pParent)
		m_pParent->RemoveChild(this);

	m_pParent = pParent;
	
	if (m_pParent)
		m_pParent->AddChild(this);
}

engine::GameObject* engine::GameObject::GetChildAt(int index) const
{
	if (index < m_pChildren.size())
		return m_pChildren[index];
	else
		throw std::runtime_error(std::string("Index Invalid"));
}

void engine::GameObject::SetLocalPosition(glm::vec3 position)
{
	m_LocalPosition = position;
	SetPositionDirty();
}

void engine::GameObject::UpdateWorldPositon()
{
	if (m_IsPositionDirty)
	{
		if (m_pParent)
			m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
		else
			m_WorldPosition = m_LocalPosition;
	}
}

glm::vec3 engine::GameObject::GetWorldPosition()
{
	if (m_IsPositionDirty)
		UpdateWorldPositon();
	return m_WorldPosition;
}

void engine::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.emplace_back(pChild);
}

void engine::GameObject::RemoveChild(GameObject* pChild)
{
	if (!pChild)
		return;

	auto lastValid = std::remove_if(std::begin(m_pChildren), std::end(m_pChildren),
		[&](GameObject* algChild) {
			return algChild == pChild;
		});
}

bool engine::GameObject::IsChild(GameObject* pParent)
{
	for (int index{}; index < pParent->GetChildCount(); ++index)
	{
		if (pParent->GetChildAt(index) == this)
			return true;
	}
	return false;
}

void engine::GameObject::SetPositionDirty()
{
	m_IsPositionDirty = true;
}
