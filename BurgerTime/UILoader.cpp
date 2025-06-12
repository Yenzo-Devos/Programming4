#include "UILoader.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "MenuComponent.h"
#include "CursorComponent.h"
#include "LeaderboardHandler.h"
#include "GameModeComponent.h"
#include "TextureComponent.h"
#include "PepperDisplayComponent.h"
#include "PointsDisplayComponent.h"
#include "LivesDisplayComponent.h"
#include "PepperComponent.h"
#include "LivesComponent.h"
#include "PointsComponent.h"

void game::UILoader::LoadStartScreenUI(dae::Scene* scene)
{
	// title if wanted

	auto pointer = CreateSimpleTextObject(glm::vec2{ 60.f, 200.f }, ">", 18);
	pointer->AddComponent<CursorComponent>();
	scene->Add(std::move(pointer));
	
	auto singlePlayerText = CreateSimpleTextObject(glm::vec2{ 80.f, 200.f }, "Singleplayer", 18);
	auto coopText = CreateSimpleTextObject(glm::vec2{ 80.f, 250.f }, "Co-op mode", 18);
	auto versusText = CreateSimpleTextObject(glm::vec2{ 80.f, 300.f }, "Versus mode", 18);
	
	auto menu = scene->CreateObject();
	menu->GiveTag("menu");
	menu->AddComponent<MenuComponent>(false);
	menu->GetComponent<MenuComponent>()->AddMenuItem(singlePlayerText.get());
	menu->GetComponent<MenuComponent>()->AddMenuItem(coopText.get());
	menu->GetComponent<MenuComponent>()->AddMenuItem(versusText.get());

	scene->Add(std::move(singlePlayerText));
	scene->Add(std::move(coopText));
	scene->Add(std::move(versusText));
	scene->Add(std::move(menu));
}

void game::UILoader::LoadGameUI(dae::Scene* scene)
{
	auto pepperTextObj = CreateSimpleTextObject(glm::vec2{ 310.f, 4.f }, "PEPPER", 18);
	scene->Add(std::move(pepperTextObj));
	auto scoreTextObj = CreateSimpleTextObject(glm::vec2{ 0.f, 4.f }, "SCORE", 18);
	scene->Add(std::move(scoreTextObj));

	auto pepperCountObj = CreateSimpleTextObject(glm::vec2{ 400.f, 30.f }, "5", 18);
	pepperCountObj->AddComponent<game::PepperDisplayComponent>(pepperCountObj->GetComponent<dae::TextComponent>());
	auto chefPointsObj = CreateSimpleTextObject(glm::vec2{ 4.f, 24.f }, "0", 18);
	chefPointsObj->AddComponent<game::PointsDisplayComponent>(chefPointsObj->GetComponent<dae::TextComponent>());	
	
	auto chefLivesObj = scene->CreateObject();
	chefLivesObj->SetLocalPosition(glm::vec3{ 0.f, 480.f, 0.f });
	chefLivesObj->AddComponent<dae::RenderComponent>(true);
	chefLivesObj->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{ 0, 464, 16, 16 }, dae::RenderComponent::Rect{ 0, 0, 16, 16 }, 0, -16);
	chefLivesObj->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{ 0, 448, 16, 16 }, dae::RenderComponent::Rect{ 0, 0, 16, 16 }, 0, -32);
	chefLivesObj->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{ 0, 432, 16, 16 }, dae::RenderComponent::Rect{ 0, 0, 16, 16 }, 0, -48);
	chefLivesObj->AddComponent<dae::TextureComponent>(chefLivesObj->GetComponent<dae::RenderComponent>());
	chefLivesObj->GetComponent<dae::TextureComponent>()->LoadTexture("ui_objects/life_texture.png");
	chefLivesObj->AddComponent<game::LivesDisplayComponent>(chefLivesObj->GetComponent<dae::TextureComponent>());

	auto chefObj = scene->GetObjectByTag("player0");
	auto pepperObj = scene->GetObjectByTag("pepper");
	pepperObj->GetComponent<game::PepperComponent>()->AddObserver(pepperCountObj->GetComponent<game::PepperDisplayComponent>());
	chefObj->GetComponent<game::PointsComponent>()->AddObserver(chefPointsObj->GetComponent<game::PointsDisplayComponent>());
	
	auto gamemode = dae::SceneManager::GetInstance().GetGameMode();
	chefObj->GetComponent<game::LivesComponent>()->AddObserver(chefLivesObj->GetComponent<game::LivesDisplayComponent>());
	chefObj->GetComponent<game::LivesComponent>()->AddObserver(gamemode->GetComponent<game::GameModeComponent>());
	scene->Add(std::move(pepperCountObj));
	scene->Add(std::move(chefLivesObj));
	scene->Add(std::move(chefPointsObj));
}

void game::UILoader::LoadLeaderBoardUI(dae::Scene* scene)
{
	auto scoresEntries = LeaderboardHandler::GetInstance().CreateScoreboard("../Data/leaderboard.txt");
	glm::vec2 pos{ 140.f, 50.f };
	for (auto entry : scoresEntries)
	{
		auto nameObj = CreateSimpleTextObject(pos, entry.name, 18);
		scene->Add(std::move(nameObj));
		auto scoreObj = CreateSimpleTextObject(glm::vec2{pos.x + 70.f, pos.y}, std::to_string(entry.score), 18);
		scene->Add(std::move(scoreObj));
		pos.y += 40.f;
	}

	auto cursor = CreateSimpleTextObject(glm::vec2{ pos.x, pos.y + 30.f }, "^", 18);
	cursor->AddComponent<CursorComponent>();
	scene->Add(std::move(cursor));
	
	auto letter1 = CreateSimpleTextObject(pos, "A", 18);
	LeaderboardHandler::GetInstance().AddLetterObject(letter1.get());
	auto letter2 = CreateSimpleTextObject(glm::vec2{pos.x + 20.f, pos.y}, "A", 18);
	LeaderboardHandler::GetInstance().AddLetterObject(letter2.get());
	auto letter3 = CreateSimpleTextObject(glm::vec2{ pos.x + 40.f, pos.y }, "A", 18);
	LeaderboardHandler::GetInstance().AddLetterObject(letter3.get());

	int finalScore = dae::SceneManager::GetInstance().GetGameMode()->GetComponent<GameModeComponent>()->GetEndPoints();
	auto scoreObj = CreateSimpleTextObject(glm::vec2{ pos.x + 70.f, pos.y }, std::to_string(finalScore), 18);
	scene->Add(std::move(scoreObj));

	auto menu = scene->CreateObject();
	menu->GiveTag("menu");
	menu->AddComponent<MenuComponent>(true);
	menu->GetComponent<MenuComponent>()->AddMenuItem(letter1.get());
	menu->GetComponent<MenuComponent>()->AddMenuItem(letter2.get());
	menu->GetComponent<MenuComponent>()->AddMenuItem(letter3.get());

	scene->Add(std::move(letter1));
	scene->Add(std::move(letter2));
	scene->Add(std::move(letter3));
	scene->Add(std::move(menu));
}

std::unique_ptr<dae::GameObject> game::UILoader::CreateSimpleTextObject(glm::vec2 pos, const std::string& text, int fontSize)
{
	auto textObj = std::make_unique<dae::GameObject>();
	textObj->SetLocalPosition(glm::vec3{ pos.x, pos.y, 0.f });
	textObj->GiveTag(text);
	textObj->AddComponent<dae::RenderComponent>();
	textObj->AddComponent<dae::TextComponent>(textObj->GetComponent<dae::RenderComponent>());
	textObj->GetComponent<dae::TextComponent>()->SetText(text);
	textObj->GetComponent<dae::TextComponent>()->SetFont("ui_objects/burger_time_font.otf", static_cast<uint8_t>(fontSize));
	return textObj;
}
