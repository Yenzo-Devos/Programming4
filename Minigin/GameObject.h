#pragma once
#include <memory>
#include <vector>
#include <stdexcept>

#include "Transform.h"
#include "BaseComponent.h"
namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float fixedDeltaTime);
		virtual void Render() const;

		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		std::vector<std::unique_ptr<BaseComponent>> m_ComponentVec{};
	
	// templated component functions
	public:
		template <typename Comp, typename... Args>
		void AddComponent(Args&&... args)
		{
			if (std::is_base_of<BaseComponent, Comp>::value)
			{
				auto comp = std::make_unique<Comp>(this, std::forward<Args>(args)...);
				m_ComponentVec.emplace_back(std::move(comp));
			}
			else
				throw std::runtime_error("T must inherit from BaseComponent");
			
		}

		template <typename Comp>
		void RemoveComponent()
		{
			Comp* tempComp;
			for (int index{}; index < m_ComponentVec.size(); ++index)
			{
				tempComp = dynamic_cast<Comp*>(m_ComponentVec[index].get());
				if (tempComp)
					tempComp->SetDead();
			}
		}

		template <typename Comp>
		Comp* GetComponent()
		{
			Comp* tempComp;
			for (auto& comp : m_ComponentVec)
			{
				tempComp = dynamic_cast<Comp*>(comp.get());
				if (tempComp)
					return tempComp;
			}
			throw std::runtime_error("component not found");
		}

		template <typename Comp>
		bool HasComponent()
		{
			Comp* tempComp;
			for (auto comp : m_ComponentVec)
			{
				tempComp = dynamic_cast<Comp*>(comp.get());
				if (tempComp)
					return true;
				else
					return false;
			}
			return false;
		}
	};
}
