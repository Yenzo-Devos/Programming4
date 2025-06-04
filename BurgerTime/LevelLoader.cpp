#include "LevelLoader.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

// components and object to create objects
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "LivesComponent.h"

void game::LevelLoader::LoadLevel(const std::string& dataPath, const std::string& fileName, dae::Scene& scene)
{
	using json = nlohmann::json;

	try {
		std::ifstream inputFile(dataPath + fileName);
		if (!inputFile.is_open()) {
			std::cerr << "Failed to open file: " << dataPath + fileName << '\n';
			return;
		}

		json jsonData;
		inputFile >> jsonData;

		const auto& staticObject = jsonData["staticObjects"];
		for (const auto& ladder : staticObject["ladder"])
			scene.Add(CreateLadder(ladder["x"], ladder["y"], ladder["length"]));
		for (const auto& platform : staticObject["platform"])
			scene.Add(CreatePlatform(platform["idGroup"], platform["x"], platform["y"]));
		for (const auto& plate : staticObject["plate"])
			scene.Add(CreatePlate(plate["idGroup"], plate["x"], plate["y"]));
		for (const auto& floor : staticObject["floor"])
			scene.Add(CreateFloor(floor["x"], floor["y"]));

		auto dynamicObject = jsonData["dynamicObjects"];
		for (const auto& ingredient : dynamicObject["ingredient"])
			scene.Add(CreateIngredient(ingredient["type"], ingredient["idGroup"], ingredient["x"], ingredient["y"]));
		for (const auto& player : dynamicObject["player"])
			scene.Add(CreatePlayer(player["id"], player["x"], player["y"]));
		for (const auto& enemy : dynamicObject["enemy"])
			scene.Add(CreateEnemy(enemy["type"], enemy["x"], enemy["y"]));
	}
	catch (const std::exception& e)
	{
		std::cerr << "parsing failed" << e.what() << '\n';
	}
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreateLadder(float x, float y, int length)
{
	auto ladder = std::make_unique<dae::GameObject>();
	ladder->GiveTag("ladder");
	ladder->SetLocalPosition(glm::vec3(x, y, 0.f));
	
	const std::string textureFileName = "static_objects/ladder" + std::to_string(length) + ".png";
	ladder->AddComponent<dae::RenderComponent>();
	ladder->AddComponent<dae::TextureComponent>(ladder->GetComponent<dae::RenderComponent>());
	ladder->GetComponent<dae::TextureComponent>()->LoadTexture(textureFileName);
	// add collision comp for ladder and if needed a ladder component
	return ladder;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreatePlatform(int, float x, float y)
{
	auto platform = std::make_unique<dae::GameObject>();
	platform->GiveTag("platform");
	platform->SetLocalPosition(glm::vec3(x, y, 0.f));
	
	platform->AddComponent<dae::RenderComponent>();
	platform->AddComponent<dae::TextureComponent>(platform->GetComponent<dae::RenderComponent>());
	platform->GetComponent<dae::TextureComponent>()->LoadTexture("static_objects/platform.png");
	// add platformcompnent and collisionComp
	
	return platform;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreatePlate(int, float x, float y)
{
	auto plate = std::make_unique<dae::GameObject>();
	plate->GiveTag("plate");
	plate->SetLocalPosition(glm::vec3(x, y, 0.f));

	plate->AddComponent<dae::RenderComponent>();
	plate->AddComponent<dae::TextureComponent>(plate->GetComponent<dae::RenderComponent>());
	plate->GetComponent<dae::TextureComponent>()->LoadTexture("static_objects/plate.png");
	// add plateComponent and collisionComp

	return plate;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreateFloor(float x, float y)
{
	auto floor = std::make_unique<dae::GameObject>();
	floor->GiveTag("floor");
	floor->SetLocalPosition(glm::vec3(x, y, 0.f));

	floor->AddComponent<dae::RenderComponent>();
	floor->AddComponent<dae::TextureComponent>(floor->GetComponent<dae::RenderComponent>());
	floor->GetComponent<dae::TextureComponent>()->LoadTexture("static_objects/floor.png");
	// add collisionComp

	return floor;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreateIngredient(int type, int, float x, float y)
{
	auto ingredient = std::make_unique<dae::GameObject>();
	ingredient->GiveTag("ingredient");
	ingredient->SetLocalPosition(glm::vec3(x, y, 0.f));

	const std::string textureFileName = "dynamic_objects/ingredient" + std::to_string(type) + ".png";
	ingredient->AddComponent<dae::RenderComponent>();
	ingredient->AddComponent<dae::TextureComponent>(ingredient->GetComponent<dae::RenderComponent>());
	ingredient->GetComponent<dae::TextureComponent>()->LoadTexture(textureFileName);
	// add collisionComp and ingredientComp

	return ingredient;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreatePlayer(int id, float x, float y)
{
	// check if game is single or multiplayer mode?
	
	auto player = std::make_unique<dae::GameObject>();
	player->SetLocalPosition(glm::vec3(x, y, 0.f));

	std::string spriteFileName;
	if (id == 0)
	{
		spriteFileName = "dynamic_objects/player0_sprite_sheet.png";
		player->GiveTag("player0");
	}
	else if (id == 1)
	{
		spriteFileName = "dynamic_objects/player0_sprite_sheet.png";
		player->GiveTag("player1");
	}
	else throw std::runtime_error("player id incorrect, failed to load player correctly");

	player->AddComponent<dae::RenderComponent>(true);
	player->AddComponent<dae::SpriteComponent>(player->GetComponent<dae::RenderComponent>(), 16, 16);
	player->GetComponent<dae::SpriteComponent>()->LoadTexture(spriteFileName);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("idle", 1, 0, 1.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkLeft", 3, 1, 1.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkRight", 3, 2, 1.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkUp", 3, 3, 1.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkDown", 3, 4, 1.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("winning", 2, 5, 1.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("dying", 5, 6, 1.f);
	player->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("dying");
	player->AddComponent<game::LivesComponent>(3);

	// add collisioncomp and playercomp

	return player;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreateEnemy(const std::string& type, float x, float y)
{
	auto enemy = std::make_unique<dae::GameObject>();
	enemy->GiveTag("enemy");
	enemy->SetLocalPosition(glm::vec3(x, y, 0.f));

	const std::string textureFileName = "dynamic_objects/" + type + "_sprite_sheet.png";
	enemy->AddComponent<dae::RenderComponent>(true);
	enemy->AddComponent<dae::SpriteComponent>(enemy->GetComponent<dae::RenderComponent>(), 16, 16);
	enemy->GetComponent<dae::SpriteComponent>()->LoadTexture(textureFileName);
	enemy->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkLeft", 2, 1, 1.f);
	enemy->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkRight", 2, 2, 1.f);
	enemy->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkUp", 2, 3, 1.f);
	enemy->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkDown", 2, 4, 1.f);
	enemy->GetComponent<dae::SpriteComponent>()->LoadAnimationData("dying", 4, 5, 1.f);
	enemy->GetComponent<dae::SpriteComponent>()->LoadAnimationData("sprayed", 2, 6, 1.f);
	enemy->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("walkLeft");
	
	// add collisioncomp and EnemyComp

	return enemy;
}
