#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		std::unique_ptr<GameObject> CreateObject();
		
		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		GameObject* GetObjectByTag(const std::string& tag);
		std::vector<GameObject*> GetAllObjectByTag(const std::string& tag);

		void Update(float deltaTime);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<std::unique_ptr<GameObject>> m_pObjects{};

		static unsigned int m_idCounter; 
	};

}
