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

		void Update();
		void FixedUpdate(float fixedDeltaTime);
		void Render();
		void RenderUI();
		void RemoveDead();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
