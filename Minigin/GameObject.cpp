#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"

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
