#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Scene.h"

namespace dae
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void CreateScene(const std::string& name);
		Scene& GetSceneByName(const std::string& name) const;

		void Update(float deltaTime);
		void Render();
		void RemoveDead();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_Scenes;
	};
}
