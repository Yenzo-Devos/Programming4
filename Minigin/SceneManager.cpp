#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	m_pGameMode->Update(deltaTime);
	m_ActiveScene->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	m_ActiveScene->Render();
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	for (const auto& scene : m_pScenes)
		if (scene->GetName() == name)
		{
			m_ActiveScene = scene.get();
		}
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	auto scene = std::make_unique<Scene>(name);
	m_ActiveScene = scene.get();
	m_pScenes.emplace_back(std::move(scene));
	return m_ActiveScene;
}
