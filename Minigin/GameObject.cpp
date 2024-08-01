#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject()
{
	for (int index{}; index < m_pComponentVec.size(); ++index)
	{
		delete m_pComponentVec[index];
		m_pComponentVec[index] = nullptr;
	}
}

void dae::GameObject::Update(float deltaTime)
{
	deltaTime;
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

void dae::GameObject::SetTexture(const std::string& filename)
{
	filename;
	//m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
