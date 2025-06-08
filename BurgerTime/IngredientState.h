#pragma once
#include <memory>
namespace game
{
	class IngredientComponent;
	class IngredientState
	{
	public:
		virtual ~IngredientState() {}
		virtual void Update(float) {}
		virtual std::unique_ptr<IngredientState> HandleState(IngredientComponent&) { return nullptr; }
		virtual void OnEnter(IngredientComponent&) {}
		virtual void OnExit(IngredientComponent&) {}
	};
}

