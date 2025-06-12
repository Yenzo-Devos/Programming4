#include "UILoader.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "MenuComponent.h"

void game::UILoader::LoadStartScreenUI(dae::Scene& scene)
{
	// title if wanted

	auto pointer = CreateSimpleTextObject(glm::vec2{ 60.f, 200.f }, ">", 18);
	scene.Add(std::move(pointer));
	
	auto singlePlayerText = CreateSimpleTextObject(glm::vec2{ 80.f, 200.f }, "Singleplayer", 18);
	auto coopText = CreateSimpleTextObject(glm::vec2{ 80.f, 250.f }, "Co-op mode", 18);
	auto versusText = CreateSimpleTextObject(glm::vec2{ 80.f, 300.f }, "Versus mode", 18);
	
	auto menu = scene.CreateObject();
	menu->GiveTag("menu");
	menu->AddComponent<MenuComponent>(false);
	menu->GetComponent<MenuComponent>()->AddMenuItem(singlePlayerText.get());
	menu->GetComponent<MenuComponent>()->AddMenuItem(coopText.get());
	menu->GetComponent<MenuComponent>()->AddMenuItem(versusText.get());

	scene.Add(std::move(singlePlayerText));
	scene.Add(std::move(coopText));
	scene.Add(std::move(versusText));
	scene.Add(std::move(menu));
}

void game::UILoader::LoadLeaderBoardUI(dae::Scene&)
{
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
