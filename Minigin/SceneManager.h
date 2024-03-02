#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace engine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float deltaTime);
		void FixedUpdate(float fixedDeltaTime);
		void Render();
		void RemoveDead();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
