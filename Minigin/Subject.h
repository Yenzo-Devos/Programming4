#pragma once
#include "Observer.h"

namespace dae
{
	class GameObject;
	enum class Event;

	class Subject
	{
	public:
		Subject();
		virtual ~Subject() = default;

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
		void Broadcast(GameObject* pGameObject, Event event);

	private:
		Observer* m_pFirstObserver;
	};
}