#pragma once
#include "BaseComponent.h"
#include <vector>
#include <glm.hpp>

namespace game
{
	class MenuComponent : public dae::BaseComponent
	{
	public:
		MenuComponent(dae::GameObject* pOwner, bool areItemsHorizontal);
		~MenuComponent() = default;

		MenuComponent(const MenuComponent& other) = delete;
		MenuComponent(MenuComponent&& other) = delete;
		MenuComponent& operator=(const MenuComponent& other) = delete;
		MenuComponent& operator=(MenuComponent&& other) = delete;

		void Update(float) override {}

		void AddMenuItem(dae::GameObject* pMenuItem);
		glm::vec3 GetNextItemLocation(bool isNext);
		bool IsOrderHorizontal() const { return m_isOrderedHorizontal; }
		int GetItemSelected() const { return m_ItemSelected; }

	private:
		bool m_isOrderedHorizontal;
		int m_ItemSelected{ 0 };
		std::vector<dae::GameObject*> m_pMenuItems;
	};
}


