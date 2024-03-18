#include "Windows.h"
#include "XController.h"
#include "Xinput.h"
#include <array>

class input::XController::XControllerImpl
{
public:
    XControllerImpl(unsigned int input);
    ~XControllerImpl() = default;

    void PollInput();
    bool IsDownThisFrame(unsigned int input) const;
    bool IsUpThisFrame(unsigned int input) const;
    bool IsPressed(unsigned int input) const;
    unsigned int Remap(ControllerInput input);
private:
    XINPUT_STATE m_CurrentState{};
    XINPUT_STATE m_LastState{};

    unsigned int m_ButtonsPressedThisFrame{};
    unsigned int m_ButtonsReleasedThisFrame{};
    unsigned int m_ControllerIndex{};
};

input::XController::XControllerImpl::XControllerImpl(unsigned int input)
    : m_ControllerIndex{ input }
{
}

void input::XController::XControllerImpl::PollInput()
{
    CopyMemory(&m_LastState, &m_CurrentState, sizeof(XINPUT_STATE));
    ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
    XInputGetState(m_ControllerIndex, &m_CurrentState);

    auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_LastState.Gamepad.wButtons;
    m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
    m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool input::XController::XControllerImpl::IsDownThisFrame(unsigned int input) const
{
    return m_ButtonsPressedThisFrame & input;
}

bool input::XController::XControllerImpl::IsUpThisFrame(unsigned int input) const
{
    return m_ButtonsReleasedThisFrame & input;
}

bool input::XController::XControllerImpl::IsPressed(unsigned int input) const
{
    return m_CurrentState.Gamepad.wButtons & input;
}

unsigned int input::XController::XControllerImpl::Remap(ControllerInput input)
{
    switch (input)
    {
    case input::ControllerInput::faceUp:
        return XINPUT_GAMEPAD_Y;
    case input::ControllerInput::faceDown:
        return XINPUT_GAMEPAD_A;
    case input::ControllerInput::faceLeft:
        return XINPUT_GAMEPAD_X;
    case input::ControllerInput::faceRight:
        return XINPUT_GAMEPAD_B;
    case input::ControllerInput::dPadUp:
        return XINPUT_GAMEPAD_DPAD_UP;
    case input::ControllerInput::dPadDown:
        return XINPUT_GAMEPAD_DPAD_DOWN;
    case input::ControllerInput::dPadLeft:
        return XINPUT_GAMEPAD_DPAD_LEFT;
    case input::ControllerInput::dPadRight:
        return XINPUT_GAMEPAD_DPAD_RIGHT;
    case input::ControllerInput::joystickLeft:
        return XINPUT_GAMEPAD_LEFT_THUMB;
    case input::ControllerInput::joystickRight:
        return XINPUT_GAMEPAD_RIGHT_THUMB;
    case input::ControllerInput::bumperLeft:
        return XINPUT_GAMEPAD_LEFT_SHOULDER;
    case input::ControllerInput::bumperRight:
        return XINPUT_GAMEPAD_RIGHT_SHOULDER;
    default:
        return unsigned int(-1);
    }
}

input::XController::XController(unsigned int controllerIndex)
    : m_pImpl{ new XControllerImpl{controllerIndex} }
{
}

input::XController::~XController()
{
    delete m_pImpl;
}

void input::XController::PollInput()
{
    m_pImpl->PollInput();
}

bool input::XController::ValidateInput(ControllerInput input, InputType inputType)
{
    switch (inputType)
    {
    case input::InputType::IsDown:
        return m_pImpl->IsDownThisFrame(m_pImpl->Remap(input));
    case input::InputType::IsUp:
        return m_pImpl->IsUpThisFrame(m_pImpl->Remap(input));
    case input::InputType::Pressed:
        return m_pImpl->IsPressed(m_pImpl->Remap(input));
    default:
        return false;
    }
}