#define WIN32_LEAN_AND_MEAN
#include "GamePad.h"

#include <Windows.h>
#include <Xinput.h>

class dae::GamePad::GamePadImpl
{
public:
    GamePadImpl(int id);
    ~GamePadImpl() = default;

    GamePadImpl(const GamePadImpl& other) = delete;
    GamePadImpl(GamePadImpl&& other) = delete;
    GamePadImpl& operator=(const GamePadImpl& other) = delete;
    GamePadImpl& operator=(GamePadImpl&& other) = delete;

    void Update(float);

    bool IsButtonDownThisFrame(GamePadButton button) const;
    bool IsButtonUpThisFrame(GamePadButton button) const;
    bool IsButtonHeld(GamePadButton button) const;

    int GetID() const;
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

void dae::GamePad::GamePadImpl::Update(float)
{
    CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
    ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
    XInputGetState(m_GamePadID, &m_CurrentState);

    auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
    m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
    m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool dae::GamePad::GamePadImpl::IsButtonDownThisFrame(GamePadButton button) const
{
    return m_ButtonsPressedThisFrame & static_cast<unsigned int>(button);
}

bool dae::GamePad::GamePadImpl::IsButtonUpThisFrame(GamePadButton button) const
{
    return m_ButtonsReleasedThisFrame & static_cast<unsigned int>(button);
}

bool dae::GamePad::GamePadImpl::IsButtonHeld(GamePadButton button) const
{
    return m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button);
}

int dae::GamePad::GamePadImpl::GetID() const
{
    return m_GamePadID;
}

dae::GamePad::GamePad(int id)
    : m_pImpl{ std::make_unique<GamePadImpl>(id) }
{
    
}

dae::GamePad::~GamePad() = default;

void dae::GamePad::Update(float deltaTime)
{
    m_pImpl->Update(deltaTime);
}

bool dae::GamePad::IsButtonDownThisFrame(GamePadButton button) const
{
    return m_pImpl->IsButtonDownThisFrame(button);
}

bool dae::GamePad::IsButtonUpThisFrame(GamePadButton button) const
{
    return m_pImpl->IsButtonUpThisFrame(button);
}

bool dae::GamePad::IsButtonHeld(GamePadButton button) const
{
    return m_pImpl->IsButtonHeld(button);
}

int dae::GamePad::GetID() const
{
    return m_pImpl->GetID();
}