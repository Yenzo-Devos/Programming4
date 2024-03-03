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
	}
}


void engine::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void engine::GameObject::RemoveDeadComponents()
{
	for (int componentIndex{ 0 }; componentIndex < m_pComponentVector.size(); ++componentIndex)
	{
		if (m_pComponentVector[componentIndex].get()->GetIsDead())
			m_pComponentVector[componentIndex].reset();
	}
}

void engine::GameObject::SetParent(GameObject* pParent)
{
	if (!pParent || IsChild(pParent) || m_pParent == pParent)
		return;

	if (m_pParent)
		m_pParent = nullptr;
	m_pParent = pParent;
	m_pParent->AddChild(this);
}

engine::GameObject* engine::GameObject::GetChildAt(int index) const
{
	if (index < m_pChildren.size())
		return m_pChildren[index];
	else
		throw std::runtime_error(std::string("Index Invalid"));
}

void engine::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.emplace_back(pChild);
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
