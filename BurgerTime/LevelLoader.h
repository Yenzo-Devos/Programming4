#pragma once
#include "Singleton.h"
#include "Scene.h"

#include <string>
#include <memory>

namespace game
{
	class dae::GameObject;

	class LevelLoader final : public dae::Singleton<LevelLoader>
	{
	public:
		~LevelLoader() = default;

		LevelLoader(const LevelLoader& other) = delete;
		LevelLoader(LevelLoader&& other) = delete;
		LevelLoader& operator=(const LevelLoader& other) = delete;
		LevelLoader& operator=(LevelLoader&& other) = delete;
	
		void LoadLevel(const std::string& dataPath, const std::string& fileName, dae::Scene& scene);
	private:
		friend class Singleton<LevelLoader>;
		LevelLoader() = default;

		// static objects
		std::unique_ptr<dae::GameObject> CreateLadder(int x, int y, int length);
		std::unique_ptr<dae::GameObject> CreatePlatform(int idGroup, int x, int y);
		std::unique_ptr<dae::GameObject> CreatePlate(int idGroup, int x, int y);
		std::unique_ptr<dae::GameObject> CreateFloor(int x, int y);
		std::unique_ptr<dae::GameObject> CreateWalkableObject(int x, int y, int width);

		// dynamic objects
		std::unique_ptr<dae::GameObject> CreateIngredient(int type, int idGroup, int x, int y, std::vector<dae::GameObject*> plateVec);
		std::unique_ptr<dae::GameObject> CreatePlayer(int id, int x, int y);
		std::unique_ptr<dae::GameObject> CreatePepper();
		std::unique_ptr<dae::GameObject> CreateEnemy(const std::string& type, int x, int y);
		
	};
}