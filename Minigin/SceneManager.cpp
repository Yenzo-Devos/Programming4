#include "SceneManager.h"

#include <stdexcept>

void dae::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
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
