#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject()
{
	for (int index{}; index < static_cast<int>(m_pComponentVec.size()); ++index)
	{
		delete m_pComponentVec[index];
		m_pComponentVec[index] = nullptr;
	}
}

void dae::GameObject::Update(float deltaTime)
{
	//deltaTime;
	for (const auto& component : m_pComponentVec)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	//const auto& pos = m_transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	for (const auto& component : m_pComponentVec)
	{
		component->Render();
	}
}

void dae::GameObject::SetParent(GameObject* parent)
{
	if (parent == this || IsChild(parent) || m_pParent == parent)
		return;

	if (!m_pParent)
		SetLocalPos(GetWorldPos());
	else
	{
		SetLocalPos(GetWorldPos() - parent->GetWorldPos());
		SetPositionDirty();
	}

	if (m_pParent)
		m_pParent->RemoveChild(this);

	m_pParent = parent;

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
		[&](GameObject* child) {
			return child == pChild;
		});
}

bool dae::GameObject::IsChild(GameObject* pParent)
{
	for (int index{}; index < static_cast<int>(pParent->GetChildCount()); ++index)
	{
		if (pParent->GetChildAt(index) == this)
			return true;
	}
	return false;
}

void dae::GameObject::SetLocalPos(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

const glm::vec3& dae::GameObject::GetWorldPos()
{
	if (m_IsPosDirty)
		UpdateWorldPos();
	return m_WorldPosition;
}

void dae::GameObject::UpdateWorldPos()
{
	if (m_IsPosDirty)
	{
		if (m_pParent == nullptr)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = m_pParent->GetWorldPos() + m_LocalPosition;
	}
	m_IsPosDirty = false;
}
