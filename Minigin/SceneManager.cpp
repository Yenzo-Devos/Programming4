#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_pScenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_pScenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::SetActiveScene(const std::string& name, std::unique_ptr<GameObject> pGameMode)
{
	for (const auto& scene : m_pScenes)
		if (scene->GetName() == name)
		{
			scene->Add(std::move(pGameMode));
			m_ActiveScene = scene.get();
			//->Add(std::move(pGameMode));
		}
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	//const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	auto scene = std::make_unique<Scene>(name);
	m_ActiveScene = scene.get();
	m_pScenes.emplace_back(std::move(scene));
	return m_ActiveScene;
}
