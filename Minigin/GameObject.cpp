#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	deltaTime;
}

void dae::GameObject::FixedUpdate(float fixedDeltaTime)
{
	fixedDeltaTime;
}

void dae::GameObject::Render() const
{

}


void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::RemoveDead()
{

}
