#include "SceneManager.h"
#include "Scene.h"

void engine::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void engine::SceneManager::FixedUpdate(float fixedDeltaTime)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedDeltaTime);
	}
}

void engine::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void engine::SceneManager::RenderUI()
{
	for (const auto& scene : m_scenes)
	{
		scene->RenderUI();
	}
}

void engine::SceneManager::RemoveDead()
{
	for (const auto& scene : m_scenes)
	{
		scene->RemoveDead();
	}
}

engine::Scene& engine::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
