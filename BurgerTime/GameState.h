#pragma once
#include <memory>
namespace dae
{
	class GameObject;
}

namespace game
{
	class GameState
	{
	public:
		virtual ~GameState() = default;
		virtual void Update(float) {}
		virtual std::unique_ptr<GameState> HandleState(dae::GameObject*) { return nullptr; }
		virtual void OnEnter(dae::GameObject*) {}
		virtual void OnExit(dae::GameObject*) {}
	};
}


