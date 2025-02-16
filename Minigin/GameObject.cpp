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
