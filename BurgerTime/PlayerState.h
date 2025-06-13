#pragma once
#include "GameObject.h"
#include <memory>

namespace game
{
	class PlayerState
	{
	public:
		virtual ~PlayerState() = default;
		virtual void Update(float) {}
		virtual std::unique_ptr<PlayerState> HandleState(dae::GameObject*) { return nullptr; }
		virtual void OnEnter(dae::GameObject*) {}
		virtual void OnExit(dae::GameObject*) {}
	};
}