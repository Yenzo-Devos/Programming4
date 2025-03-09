#define WIN32_LEAN_AND_MEAN
#include "GamePad.h"
#include <Xinput.h>

class dae::GamePad::GamePadImpl
{
public:
    GamePadImpl(int id);
    void Update(float deltaTime);

    bool IsButtonDownThisFrame(unsigned int button) const;
    bool IsButtonUpThisFrame(unsigned int button) const;
    bool IsHeld(unsigned int button) const;
private:
    int m_GamePadID;

    XINPUT_STATE m_CurrentState{};
    XINPUT_STATE m_PreviousState{};

    WORD m_ButtonsPressedThisFrame{};
    WORD m_ButtonsReleasedThisFrame{};
};

dae::GamePad::GamePadImpl::GamePadImpl(int id)
    : m_GamePadID{ id }
{
    ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
    ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
}

void dae::GamePad::GamePadImpl::Update(float deltaTime)
{
    CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
    ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
    XInputGetState(m_GamePadID, &m_CurrentState);

    auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
    m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
    m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool dae::GamePad::GamePadImpl::IsButtonDownThisFrame(unsigned int button) const
{
    return m_ButtonsPressedThisFrame & button;
}

bool dae::GamePad::GamePadImpl::IsButtonUpThisFrame(unsigned int button) const
{
    return m_ButtonsReleasedThisFrame & button;
}

bool dae::GamePad::GamePadImpl::IsHeld(unsigned int button) const
{
    return m_CurrentState.Gamepad.wButtons & button;
}


dae::GamePad::GamePad(int id)
{
    m_pImpl = new GamePadImpl(id);
}

dae::GamePad::~GamePad()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

bool dae::GamePad::IsButtonDownThisFrame(unsigned int button) const
{
    return m_pImpl->IsButtonDownThisFrame(button);
}

bool dae::GamePad::IsButtonUpThisFrame(unsigned int button) const
{
    return m_pImpl->IsButtonUpThisFrame(button);
}

bool dae::GamePad::IsHeld(unsigned int button) const
{
    return m_pImpl->IsHeld(button);
}
