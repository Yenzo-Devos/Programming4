#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"

// component includes
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto bgObj = std::make_unique<dae::GameObject>();
	bgObj->AddComponent<dae::TextureComponent>();
	bgObj->GetComponent<dae::TextureComponent>()->LoadTexture("background.tga");
	scene.Add(std::move(bgObj));

	auto logoObj = std::make_unique<dae::GameObject>();
	logoObj->SetPosition(216.f, 180.f);
	logoObj->AddComponent<dae::TextureComponent>();
	logoObj->GetComponent<dae::TextureComponent>()->LoadTexture("logo.tga");
	scene.Add(std::move(logoObj));

	auto textObj = std::make_unique<dae::GameObject>();
	textObj->SetPosition(80.f, 20.f);
	textObj->AddComponent<dae::TextComponent>();
	textObj->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	textObj->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 36);
	scene.Add(std::move(textObj));

	auto fpsObj = std::make_unique<dae::GameObject>();
	fpsObj->SetPosition(10.f, 10.f);
	fpsObj->AddComponent<dae::TextComponent>();
	fpsObj->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 24);
	fpsObj->AddComponent<dae::FPSComponent>(fpsObj->GetComponent<dae::TextComponent>());
	scene.Add(std::move(fpsObj));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}