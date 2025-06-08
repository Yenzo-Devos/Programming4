#pragma once
#include <memory>
namespace game
{
	class PlayerComponent;

	class PlayerState
	{
	public:
		virtual ~PlayerState() {}
		virtual void Update(float) {}
		virtual std::unique_ptr<PlayerState> HandleState(PlayerComponent&) { return nullptr; }
		virtual void OnEnter(PlayerComponent&) {}
		virtual void OnExit(PlayerComponent&) {}
	};
}