#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

std::unique_ptr<GameObject> dae::Scene::CreateObject()
{
	return std::make_unique<GameObject>();
}

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}

	for (auto& object : m_objects)
	{
		if (object->GetIsDead())
			Remove(object);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		if (object->HasComponent<RenderComponent>())
		object->GetComponent<RenderComponent>()->Render();
	}
}

