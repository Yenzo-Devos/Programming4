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
		for (int index{}; index < m_ComponentVec.size(); ++index)
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

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
