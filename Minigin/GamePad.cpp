#include "GamePad.h"

bool dae::GamePad::IsButtonDownThisFrame(unsigned int button) const
{
    return false;
}

bool dae::GamePad::IsButtonUpThisFrame(unsigned int button) const
{
    return false;
}

bool dae::GamePad::IsHeld(unsigned int button) const
{
    auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
    return false;
}
