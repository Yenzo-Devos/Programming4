#include "PlayerState.h"
#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "PlayerPepperState.h"
#include "PlayerDyingState.h"
#include "PlayerWinningState.h"

namespace game
{
	PlayerIdleState PlayerState::m_Idle;
	PlayerMoveState PlayerState::m_Move;
	PlayerPepperState PlayerState::m_Pepper;
	PlayerDyingState PlayerState::m_Dying;
	PlayerWinningState PlayerState::m_Winning;
}
