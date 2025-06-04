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
		std::unique_ptr<dae::GameObject> CreateLadder(float x, float y, int length);
		std::unique_ptr<dae::GameObject> CreatePlatform(int idGroup, float x, float y);
		std::unique_ptr<dae::GameObject> CreatePlate(int idGroup, float x, float y);
		std::unique_ptr<dae::GameObject> CreateFloor(float x, float y);

		// dynamic objects
		std::unique_ptr<dae::GameObject> CreateIngredient(int type, int idGroup, float x, float y);
		std::unique_ptr<dae::GameObject> CreatePlayer(int id, float x, float y);
		std::unique_ptr<dae::GameObject> CreateEnemy(const std::string& type, float x, float y);
		
	};
}