#include "Controller.h"

#include <Windows.h>
#include <XInput.h>

class dae::Controller::ControllerImpl final
{
public:
    ControllerImpl(unsigned int input);
    ~ControllerImpl() = default;

    void PollInput();
    bool IsDownThisFrame(unsigned int input) const;
    bool IsUpThisFrame(unsigned int input) const;
    bool IsPressed(unsigned int input) const;
    unsigned int GetIndex() const { return m_ControllerIndex; }

private:
    XINPUT_STATE m_CurrentState{};
    XINPUT_STATE m_LastState{};

    unsigned int m_ButtonsPressedThisFrame{};
    unsigned int m_ButtonsReleasedThisFrame{};
    unsigned int m_ControllerIndex{};
};

dae::Controller::ControllerImpl::ControllerImpl(unsigned int input)
    : m_ControllerIndex{ input }
{
}

void dae::Controller::ControllerImpl::PollInput()
{
    CopyMemory(&m_LastState, &m_CurrentState, sizeof(XINPUT_STATE));
    ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
    XInputGetState(m_ControllerIndex, &m_CurrentState);

    auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_LastState.Gamepad.wButtons;
    m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
    m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool dae::Controller::ControllerImpl::IsDownThisFrame(unsigned int input) const
{
    return m_ButtonsPressedThisFrame & input;
}

bool dae::Controller::ControllerImpl::IsUpThisFrame(unsigned int input) const
{
    return m_ButtonsReleasedThisFrame & input;
}

bool dae::Controller::ControllerImpl::IsPressed(unsigned int input) const
{
    return m_CurrentState.Gamepad.wButtons & input;
}

void dae::Controller::PollInput()
{
    m_pImpl->PollInput();
}

bool dae::Controller::ValidateInput(ControllerInput input, InputType inputType)
{
    switch (inputType)
    {
    case dae::Controller::InputType::IsDown:
        return m_pImpl->IsDownThisFrame(static_cast<unsigned int>(input));
    case dae::Controller::InputType::IsUp:
        return m_pImpl->IsUpThisFrame(static_cast<unsigned int>(input));
    case dae::Controller::InputType::Pressed:
        return m_pImpl->IsPressed(static_cast<unsigned int>(input));
    default:
        return false;
    }
}

unsigned int dae::Controller::GetIndex() const
{
    return m_pImpl->GetIndex();
}

dae::Controller::Controller(unsigned int controllerIndex)
    : m_pImpl{ new ControllerImpl{ controllerIndex } }
{
}

dae::Controller::~Controller()
{
    delete m_pImpl;
}
