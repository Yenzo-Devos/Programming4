#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
//#include "TextObject.h"
#include <memory>

#include "TextComponent.h"
#include "TextureComponent.h"

void load()
{
	dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& scene = dae::SceneManager::GetInstance().GetSceneByName("Demo");

	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->GetComponent<dae::TextureComponent>()->LoadTexture("background.tga");
	//go->SetTexture("background.tga");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->GetComponent<dae::TextureComponent>()->LoadTexture("logo.tga");
	//go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(std::move(go));

	//auto to = std::make_unique<dae::TextObject>("Programming 4 Assignment", font);
	auto to = std::make_unique<dae::GameObject>();
 	to->AddComponent<dae::TextComponent>();
	to->GetComponent<dae::TextComponent>()->SetFont("Lingua.otf", 22);
	to->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	
	//to->SetPosition(80, 20);
	scene.Add(std::move(to));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}