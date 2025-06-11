#pragma once
namespace dae
{
	class GameObject;

	enum class Event
	{
		OnPlayerDeath,
		OnPlayerScored,
		OnIngredientFallOnPlate,
		OnIngredientLanded,
		EnemyStunned
	};

	class Observer
	{
		friend class Subject;
	public:
		Observer()
		: m_pNextObserver{ nullptr }
		{ }
		virtual ~Observer() = default;
		virtual void Broadcast(GameObject* pGameObject, Event event) = 0;

	private:
		Observer* m_pNextObserver;
	};
}