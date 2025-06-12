#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include <memory>

namespace dae
{
	class Observer;
}

namespace game
{
	class CursorComponent : dae::BaseComponent
	{
	public:
		CursorComponent(dae::GameObject* pOwner);
		virtual ~CursorComponent() = default;

		CursorComponent(const CursorComponent& other) = delete;
		CursorComponent(CursorComponent&& other) = delete;
		CursorComponent& operator=(const CursorComponent& other) = delete;
		CursorComponent& operator=(CursorComponent&& other) = delete;

		void Update(float) override {}
		void Click();
	
		void AddObserver(dae::Observer* pObserver);
		void RemoveObserver(dae::Observer* pObserver);

	private:
		std::unique_ptr<dae::Subject> m_pOnClicked;
	};
}