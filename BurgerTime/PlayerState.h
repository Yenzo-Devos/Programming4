#pragma once
namespace game
{
	class PlayerComponent;
	class PlayerState
	{
	public:
		virtual ~PlayerState() {};
		virtual void Update(float) {};
		virtual PlayerState* HandleInput(PlayerComponent&) { return this; }
		virtual void OnEnter(PlayerComponent&) {};
		virtual void OnExit(PlayerComponent&) {};
	};
}

