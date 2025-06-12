#pragma once
#include "Singleton.h"
#include "Scene.h"

#include <string>
#include <memory>

namespace game
{
	class CommandLoader final : public dae::Singleton<CommandLoader>
	{
	public:
		~CommandLoader() = default;

		CommandLoader(const CommandLoader& other) = delete;
		CommandLoader(CommandLoader&& other) = delete;
		CommandLoader& operator=(const CommandLoader& other) = delete;
		CommandLoader& operator=(CommandLoader&& other) = delete;

		void CreateStartMenuCommands(dae::Scene* pScene);
		void CreateSinglePlayerCommands(dae::Scene* pScene, dae::GameObject* pGameState);
		void CreateCoopCommands();
		void CreateVersusCommands();
		void CreateLeaderboardCommands(dae::Scene* pScene);

	private:
		friend class Singleton<CommandLoader>;
		CommandLoader() = default;
	};
}


