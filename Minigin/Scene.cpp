#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace engine;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

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

void engine::Scene::FixedUpdate(float fixedDeltaTime)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedDeltaTime);
	}
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void engine::Scene::RenderUI()
{
	for (const auto& object : m_objects)
	{
		object->RenderUI();
	}
}

void engine::Scene::RemoveDead()
{
	for (const auto& object : m_objects)
	{
		object->RemoveDeadComponents();
	}
}

