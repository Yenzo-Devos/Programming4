#pragma once
namespace game
{
	class PlayerComponent;
	class PlayerIdleState;
	class PlayerMoveState;
	class PlayerPepperState;
	class PlayerDyingState;
	class PlayerWinningState;

	class PlayerState
	{
	public:
		virtual ~PlayerState() {};
		virtual void Update(float) {};
		virtual PlayerState* HandleState(PlayerComponent&) { return this; }
		virtual void OnEnter(PlayerComponent&) {};
		virtual void OnExit(PlayerComponent&) {};

		// all states
		static PlayerIdleState m_Idle;
		static PlayerMoveState m_Move;
		static PlayerPepperState m_Pepper;
		static PlayerDyingState m_Dying;
		static PlayerWinningState m_Winning;
	};
}