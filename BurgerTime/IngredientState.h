#pragma once
#include "GameObject.h"
#include <memory>
namespace game
{
	class IngredientState
	{
	public:
		virtual ~IngredientState() {}
		virtual void Update(float) {}
		virtual std::unique_ptr<IngredientState> HandleState(dae::GameObject&) { return nullptr; }
		virtual void OnEnter(dae::GameObject&) {}
		virtual void OnExit(dae::GameObject&) {}
	};
}

