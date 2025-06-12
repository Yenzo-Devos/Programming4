#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "GameObject.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* CreateScene(const std::string& name);

		void Update(float deltaTime);
		void Render();

		dae::Scene* GetActiveScene() const { return m_ActiveScene; }
		void SetActiveScene(const std::string& name);
		void SetGameMode(std::unique_ptr<GameObject> pGameMode) { m_pGameMode = std::move(pGameMode); }
		GameObject* GetGameMode() const { return m_pGameMode.get(); }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::unique_ptr<Scene>> m_pScenes;
		Scene* m_ActiveScene{};
		std::unique_ptr<GameObject> m_pGameMode{};
	};
}
