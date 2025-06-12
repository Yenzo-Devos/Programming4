#pragma once
#include "Singleton.h"
#include "Scene.h"

#include <string>
#include <memory>

namespace game
{
	class UILoader final : public dae::Singleton<UILoader>
	{
	public:
		~UILoader() = default;

		UILoader(const UILoader& other) = delete;
		UILoader(UILoader&& other) = delete;
		UILoader& operator=(const UILoader& other) = delete;
		UILoader& operator=(UILoader&& other) = delete;

		void LoadStartScreenUI(dae::Scene& scene);
		void LoadLeaderBoardUI(dae::Scene& scene);

	private:
		friend class Singleton<UILoader>;
		UILoader() = default;

		std::unique_ptr<dae::GameObject> CreateSimpleTextObject(glm::vec2 pos, const std::string& text, int fontSize);
	};
}


