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
#include "HitboxComponent.h"
#include "PlayerComponent.h"
#include "IngredientComponent.h"
#include "FallComponent.h"
#include "PlateComponent.h"
#include "PepperComponent.h"

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
		for (const auto& walkableObject : staticObject["walkableObject"])
			scene.Add(CreateWalkableObject(walkableObject["x"], walkableObject["y"], walkableObject["width"]));

		auto dynamicObject = jsonData["dynamicObjects"];
		for (const auto& ingredient : dynamicObject["ingredient"])
			scene.Add(CreateIngredient(ingredient["type"], ingredient["idGroup"], ingredient["x"], ingredient["y"], scene.GetAllObjectByTag("plate")));
		//for (const auto& enemy : dynamicObject["enemy"])
			//scene.Add(CreateEnemy(enemy["type"], enemy["x"], enemy["y"]));
		for (const auto& player : dynamicObject["player"])
			scene.Add(CreatePlayer(player["id"], player["x"], player["y"]));
	}
	catch (const std::exception& e)
	{
		std::cerr << "parsing failed" << e.what() << '\n';
	}
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreateLadder(int x, int y, int length)
{
	auto ladder = std::make_unique<dae::GameObject>();
	ladder->GiveTag("ladder");
	ladder->SetLocalPosition(glm::vec3(x, y, 0.f));
	ladder->SetDimensions(32, length * 32);
	
	const std::string textureFileName = "static_objects/ladder" + std::to_string(length) + ".png";
	ladder->AddComponent<dae::RenderComponent>();
	ladder->AddComponent<dae::TextureComponent>(ladder->GetComponent<dae::RenderComponent>());
	ladder->GetComponent<dae::TextureComponent>()->LoadTexture(textureFileName);
	// add collision comp for ladder and if needed a ladder component
	ladder->AddComponent<dae::HitboxComponent>();
	ladder->GetComponent<dae::HitboxComponent>()->AddHitbox("main_hitbox", 0, 0, 32, 32 * length);
	return ladder;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreatePlatform(int, int x, int y)
{
	auto platform = std::make_unique<dae::GameObject>();
	platform->GiveTag("platform");
	platform->SetLocalPosition(glm::vec3(x, y, 0.f));
	platform->SetDimensions(64, 6);
	
	platform->AddComponent<dae::RenderComponent>();
	platform->AddComponent<dae::TextureComponent>(platform->GetComponent<dae::RenderComponent>());
	platform->GetComponent<dae::TextureComponent>()->LoadTexture("static_objects/platform.png");
	// add platformcompnent and collisionComp
	platform->AddComponent<dae::HitboxComponent>();
	platform->GetComponent<dae::HitboxComponent>()->AddHitbox("main_hitbox", 0, 0, 64, 6);
	
	return platform;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreatePlate(int idGroup, int x, int y)
{
	auto plate = std::make_unique<dae::GameObject>();
	plate->GiveTag("plate");
	plate->SetLocalPosition(glm::vec3(x, y, 0.f));
	plate->SetDimensions(76, 10);

	plate->AddComponent<dae::RenderComponent>();
	plate->AddComponent<dae::TextureComponent>(plate->GetComponent<dae::RenderComponent>());
	plate->GetComponent<dae::TextureComponent>()->LoadTexture("static_objects/plate.png");
	
	plate->AddComponent<dae::HitboxComponent>();
	plate->GetComponent<dae::HitboxComponent>()->AddHitbox("main_hitbox", 0, 0, 76, 10);

	plate->AddComponent<game::PlateComponent>(idGroup);
	return plate;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreateFloor(int x, int y)
{
	auto floor = std::make_unique<dae::GameObject>();
	floor->GiveTag("floor");
	floor->SetLocalPosition(glm::vec3(x, y, 0.f));
	floor->SetDimensions(32, 6);

	floor->AddComponent<dae::RenderComponent>();
	floor->AddComponent<dae::TextureComponent>(floor->GetComponent<dae::RenderComponent>());
	floor->GetComponent<dae::TextureComponent>()->LoadTexture("static_objects/floor.png");

	return floor;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreateWalkableObject(int x, int y, int width)
{
	auto walkableObj = std::make_unique<dae::GameObject>();
	walkableObj->GiveTag("walkable_object");
	walkableObj->SetLocalPosition(glm::vec3(x, y, 0.f));
	walkableObj->SetDimensions(width, 6);
	
	return walkableObj;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreateIngredient(int type, int idGroup, int x, int y, std::vector<dae::GameObject*> plateVec)
{	
	auto ingredient = std::make_unique<dae::GameObject>();
	ingredient->GiveTag("ingredient");
	ingredient->SetLocalPosition(glm::vec3(x, y, 0.f));
	ingredient->SetDimensions(64, 16);

	const std::string textureFileName = "dynamic_objects/ingredient" + std::to_string(type) + ".png";
	ingredient->AddComponent<dae::RenderComponent>(true);
	ingredient->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{x,    y, 16, 14}, dae::RenderComponent::Rect{0, 0, 16, 14});
	ingredient->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{x+16, y, 16, 14}, dae::RenderComponent::Rect{16, 0, 16, 14}, 16);
	ingredient->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{x+32, y, 16, 14}, dae::RenderComponent::Rect{32, 0, 16, 14}, 32);
	ingredient->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{x+48, y, 16, 14}, dae::RenderComponent::Rect{48, 0, 16, 14}, 48);
	ingredient->AddComponent<dae::TextureComponent>(ingredient->GetComponent<dae::RenderComponent>());
	ingredient->GetComponent<dae::TextureComponent>()->LoadTexture(textureFileName);
	// add collisionComp and ingredientComp
	ingredient->AddComponent<dae::HitboxComponent>();
	ingredient->GetComponent<dae::HitboxComponent>()->AddHitbox("left_hitbox", 0, 0, 16, 16);
	ingredient->GetComponent<dae::HitboxComponent>()->AddHitbox("left_middle_hitbox", 16, 0, 16, 16);
	ingredient->GetComponent<dae::HitboxComponent>()->AddHitbox("right_middle_hitbox", 32, 0, 16, 16);
	ingredient->GetComponent<dae::HitboxComponent>()->AddHitbox("right_hitbox", 48, 0, 16, 16);
	ingredient->AddComponent<game::IngredientComponent>();
	ingredient->AddComponent<game::FallComponent>(15.f);

	for (const auto& plate : plateVec)
		if (idGroup == plate->GetComponent<PlateComponent>()->GetID())
			ingredient->GetComponent<game::IngredientComponent>()->AddObserver(plate->GetComponent<PlateComponent>());

	return ingredient;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreateEnemy(const std::string& type, int x, int y)
{
	auto enemy = std::make_unique<dae::GameObject>();
	enemy->GiveTag("enemy");
	enemy->SetLocalPosition(glm::vec3(x, y, 0.f));
	enemy->SetDimensions(32, 32);

	const std::string textureFileName = "dynamic_objects/" + type + "_sprite_sheet.png";
	enemy->AddComponent<dae::RenderComponent>(true);
	enemy->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{ x, y, 32, 32 });
	enemy->AddComponent<dae::SpriteComponent>(enemy->GetComponent<dae::RenderComponent>(), 32, 32);
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

std::unique_ptr<dae::GameObject> game::LevelLoader::CreatePlayer(int id, int x, int y)
{
	// check if game is single or multiplayer mode?

	auto player = std::make_unique<dae::GameObject>();
	player->SetLocalPosition(glm::vec3(x, y, 0.f));
	player->SetDimensions(32, 32);

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
	player->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{ x, y, 32, 32 });
	player->AddComponent<dae::SpriteComponent>(player->GetComponent<dae::RenderComponent>(), 32, 32);
	player->GetComponent<dae::SpriteComponent>()->LoadTexture(spriteFileName);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("idle", 1, 0, 1.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkLeft", 3, 1, 10.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkRight", 3, 2, 10.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkUp", 3, 3, 10.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("walkDown", 3, 4, 10.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("winning", 2, 5, 1.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("dying", 5, 6, 1.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("sprayLeft", 1, 7, 1.f);
	player->GetComponent<dae::SpriteComponent>()->LoadAnimationData("sprayRight", 1, 8, 1.f);
	player->GetComponent<dae::SpriteComponent>()->SetCurrentAnimation("dying");
	player->AddComponent<game::LivesComponent>(3);

	// add collisioncomp and playercomp
	player->AddComponent<dae::HitboxComponent>();
	player->GetComponent<dae::HitboxComponent>()->AddHitbox("body_hitbox", 5, 0, 22, 32);
	player->GetComponent<dae::HitboxComponent>()->AddHitbox("feet_hitbox", 5, 32, 22, 6);

	auto pepper = CreatePepper();
	player->AddComponent<game::PlayerComponent>(pepper.get());
	dae::SceneManager::GetInstance().GetActiveScene().Add(std::move(pepper));
	return player;
}

std::unique_ptr<dae::GameObject> game::LevelLoader::CreatePepper()
{
	auto pepper = std::make_unique<dae::GameObject>();
	pepper->SetLocalPosition({ -50.f, -50.f, 0.f });
	pepper->SetDimensions(32, 32);

	pepper->AddComponent<dae::RenderComponent>(true);
	pepper->GetComponent<dae::RenderComponent>()->AddObjectToRender(dae::RenderComponent::Rect{ -10, -10, 32, 32 });
	pepper->AddComponent<dae::SpriteComponent>(pepper->GetComponent<dae::RenderComponent>(), 32, 32);
	pepper->GetComponent<dae::SpriteComponent>()->LoadTexture("dynamic_objects/pepper_sprite_sheet.png");
	pepper->GetComponent<dae::SpriteComponent>()->LoadAnimationData("pepperLeft", 4, 0, 8.f);
	pepper->GetComponent<dae::SpriteComponent>()->LoadAnimationData("pepperRight", 4, 1, 8.f);

	pepper->AddComponent<dae::HitboxComponent>();
	pepper->GetComponent<dae::HitboxComponent>()->AddHitbox("main_hitbox", 0, 0, 32, 32);

	pepper->AddComponent<game::PepperComponent>(pepper->GetComponent<dae::HitboxComponent>());
	return pepper;
}
