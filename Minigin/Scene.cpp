#include "Scene.h"
#include "RenderComponent.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

std::unique_ptr<GameObject> dae::Scene::CreateObject()
{
	return std::make_unique<GameObject>();
}

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_pObjects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_pObjects)
	{
		object->Update(deltaTime);
	}

	for (auto& object : m_pObjects)
	{
		if (object->GetIsDead())
			Remove(std::move(object));
	}
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		if (object->HasComponent<RenderComponent>())
		object->GetComponent<RenderComponent>()->Render();
	}
}

