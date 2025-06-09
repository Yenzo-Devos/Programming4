#pragma once
#include <memory>

namespace dae {
	class GameObject;
}
namespace game
{
	class EnemyState
	{
	public:
		virtual ~EnemyState() {}
		virtual void Update(float) {}
		virtual std::unique_ptr<EnemyState> HandleState(dae::GameObject&) { return nullptr; }
		virtual void OnEnter(dae::GameObject&) {}
		virtual void OnExit(dae::GameObject&) {}
	};
}


