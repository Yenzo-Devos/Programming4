#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	class Scene final
	{
	public:
		std::unique_ptr<GameObject> CreateObject();
		
		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveByTag(const std::string& tag);
		void RemoveAll();

		GameObject* GetObjectByTag(const std::string& tag);
		std::vector<GameObject*> GetAllObjectByTag(const std::string& tag);
		std::unique_ptr<GameObject> GetGameMode();
		std::string GetName() const { return m_Name; }

		void Update(float deltaTime);
		void Render() const;

		Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		std::string m_Name;
		std::vector<std::unique_ptr<GameObject>> m_pObjects{};
	};

}
