#include "Scene.h"
#include "RenderComponent.h"

#include <algorithm>

using namespace dae;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

std::unique_ptr<GameObject> dae::Scene::CreateObject()
{
	return std::make_unique<GameObject>();
}

void Scene::Add(std::unique_ptr<GameObject> object)
{
	if (object == nullptr)
		return;

	m_pObjects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	auto it = std::remove_if(m_pObjects.begin(), m_pObjects.end(),
		[&object](const std::unique_ptr<GameObject>& ptr) {
			return ptr.get() == object.get();
		});

	m_pObjects.erase(it, m_pObjects.end());
}

void dae::Scene::RemoveByTag(const std::string& tag)
{
	m_pObjects.erase(std::remove_if(m_pObjects.begin(), m_pObjects.end(),
			[&tag](const std::unique_ptr<GameObject>& obj) {
				return obj->GetTag() == tag;
			}),
		m_pObjects.end());
}

void Scene::RemoveAll()
{
	for (const auto& obj : m_pObjects)
		obj->SetDead();
}

GameObject* Scene::GetObjectByTag(const std::string& tag)
{
	auto it = std::find_if(m_pObjects.begin(), m_pObjects.end(),
			  [&tag](const std::unique_ptr<GameObject>& obj)
			  { return obj->GetTag() == tag; });

	return (it != m_pObjects.end()) ? it->get() : nullptr;
}

std::vector<GameObject*> Scene::GetAllObjectByTag(const std::string& tag)
{
	std::vector<GameObject*> matchingObjects;
	for (const auto& obj : m_pObjects)
		if (obj->GetTag() == tag)
			matchingObjects.emplace_back(obj.get());

	return matchingObjects;
}

std::unique_ptr<GameObject> dae::Scene::GetGameMode()
{
	for (int index{ 0 }; index < static_cast<int>(m_pObjects.size()); ++index)
	{
		if (m_pObjects[index]->GetTag() == "gamemode")
		{
			std::unique_ptr<GameObject> result = std::move(m_pObjects[index]);
			m_pObjects.erase(m_pObjects.begin() + index);
			return result;
		}
	}
	return nullptr;
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_pObjects)
	{
		if (object)
			object->Update(deltaTime);
	}

	for (auto& object : m_pObjects)
	{
		if (!object)
			continue;

		if (object->GetIsDead())
		{
			Remove(std::move(object));
			m_DoneRemoving = true;
		}
	}

	if (m_DoneRemoving)
	{
		m_pObjects.clear();
		m_DoneRemoving = false;
	}

}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		if (!object)
			return;

		if (object->HasComponent<RenderComponent>())
		object->GetComponent<RenderComponent>()->Render();
	}
}

