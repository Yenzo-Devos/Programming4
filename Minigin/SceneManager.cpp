#include "SceneManager.h"

#include <stdexcept>

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RemoveDead()
{
	for (const auto& scene : m_Scenes)
	{
		scene->RemoveDead();
	}
}

void dae::SceneManager::CreateScene(const std::string& name)
{
	m_Scenes.push_back(std::make_unique<Scene>(name));
}

dae::Scene& dae::SceneManager::GetSceneByName(const std::string& name) const
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
			return *scene;
	}
	throw std::runtime_error("Unable to find scene");
}
