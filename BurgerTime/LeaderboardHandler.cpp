#include "LeaderboardHandler.h"
#include "TextComponent.h"
#include "GameModeComponent.h"
#include <fstream>
#include <iostream>

std::vector<game::LeaderboardHandler::ScoreEntry> game::LeaderboardHandler::CreateScoreboard(const std::string& filename)
{
	m_FileName = filename;
	std::ifstream file(m_FileName);
	m_pScores.clear();

	if (!file)
	{
		std::cerr << "couldn't open file\n";
	}

	std::string name;
	int score;
	while (file >> name >> score)
		m_pScores.emplace_back(ScoreEntry{ name, score });
	return m_pScores;
}

void game::LeaderboardHandler::AddLetterObject(dae::GameObject* letterObj)
{
	m_LetterObj.emplace_back(letterObj);
}

void game::LeaderboardHandler::ChangeLetter(bool increment, int index)
{
	if (increment)
		if (m_Name[index] == 'Z')
			m_Name[index] = 'A';
		else
			m_Name[index] += 1;
	else
		if (m_Name[index] == 'A')
			m_Name[index] = 'Z';
		else
			m_Name[index] -= 1;

	std::string str(1, m_Name[index]);
	m_LetterObj[index]->GetComponent<dae::TextComponent>()->SetText(str);
}

void game::LeaderboardHandler::ConfirmName()
{
	std::string name(m_Name.begin(), m_Name.end());
	int finalScore = dae::SceneManager::GetInstance().GetGameMode()->GetComponent<GameModeComponent>()->GetEndPoints();
	m_pScores.emplace_back(ScoreEntry{ name, finalScore });
	std::sort(m_pScores.begin(), m_pScores.end(), [](const ScoreEntry& a, const ScoreEntry& b)
		{
			return a.score > b.score;
		});
	m_pScores.pop_back();
	WriteScoresToFile();
}

void game::LeaderboardHandler::WriteScoresToFile()
{
	std::ofstream file(m_FileName);
	if (!file)
	{
		std::cerr << "couldn't open file\n";
	}
	for (const auto& entry : m_pScores)
		file << entry.name << " " << entry.score << '\n';
}
