#pragma once
#include "Singleton.h"
#include "Scene.h"

namespace game
{
	class LeaderboardHandler : public dae::Singleton<LeaderboardHandler>
	{
	public:
		struct ScoreEntry {
			std::string name;
			int score;
		};

		~LeaderboardHandler() = default;

		LeaderboardHandler(const LeaderboardHandler& other) = delete;
		LeaderboardHandler(LeaderboardHandler&& other) = delete;
		LeaderboardHandler& operator=(const LeaderboardHandler& other) = delete;
		LeaderboardHandler& operator=(LeaderboardHandler&& other) = delete;

		std::vector<ScoreEntry> CreateScoreboard(const std::string& filename);
		void AddLetterObject(dae::GameObject* letterObj);
		void ChangeLetter(bool goUp, int index);
		void ConfirmName();

	private:
		friend class Singleton<LeaderboardHandler>;
		LeaderboardHandler() = default;

		void WriteScoresToFile();

		std::string m_FileName{};
		std::vector<dae::GameObject*> m_LetterObj{};
		std::vector<char> m_Name{'A', 'A', 'A'};
		std::vector<ScoreEntry> m_pScores{};
	};
}


