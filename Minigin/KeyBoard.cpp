#include "KeyBoard.h"
#include <SDL.h>
#include <vector>

class dae::KeyBoard::KeyBoardImpl
{
public:
	KeyBoardImpl();
	~KeyBoardImpl() = default;

	KeyBoardImpl(const KeyBoardImpl& other) = delete;
	KeyBoardImpl(KeyBoardImpl&& other) = delete;
	KeyBoardImpl& operator=(const KeyBoardImpl& other) = delete;
	KeyBoardImpl& operator=(KeyBoardImpl&& other) = delete;

	void Update(float);
	bool ProcessQuitGameInput() const;

	bool IsKeyDownThisFrame(SDL_Scancode key) const;
	bool IsKeyUpThisFrame(SDL_Scancode key) const;
	bool IsKeyHeld(SDL_Scancode key) const;
private:
	std::vector<Uint8> m_CurrentKeyboardState;
	std::vector<Uint8> m_PreviousKeyboardState;
};

dae::KeyBoard::KeyBoardImpl::KeyBoardImpl()
{
	int keyCount;
	SDL_GetKeyboardState(&keyCount);
	m_PreviousKeyboardState.resize(keyCount, 0);
	m_CurrentKeyboardState.resize(keyCount, 0);
}

void dae::KeyBoard::KeyBoardImpl::Update(float)
{
	//update keyboard
	m_PreviousKeyboardState = m_CurrentKeyboardState;

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	m_CurrentKeyboardState.assign(state, state + m_CurrentKeyboardState.size());
}

bool dae::KeyBoard::KeyBoardImpl::ProcessQuitGameInput() const
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			return false;
	}
	return true;
}

bool dae::KeyBoard::KeyBoardImpl::IsKeyDownThisFrame(SDL_Scancode key) const
{
	return m_CurrentKeyboardState[key] && !m_PreviousKeyboardState[key];
}

bool dae::KeyBoard::KeyBoardImpl::IsKeyUpThisFrame(SDL_Scancode key) const
{
	return !m_CurrentKeyboardState[key] && m_PreviousKeyboardState[key];
}

bool dae::KeyBoard::KeyBoardImpl::IsKeyHeld(SDL_Scancode key) const
{
	return m_CurrentKeyboardState[key];
}

dae::KeyBoard::KeyBoard()
	: m_pImpl{ std::make_unique<KeyBoardImpl>() }
{
}

dae::KeyBoard::~KeyBoard() = default;

void dae::KeyBoard::Update(float deltaTime)
{
	m_pImpl->Update(deltaTime);
}

bool dae::KeyBoard::ProcessQuitGameInput() const
{
	return m_pImpl->ProcessQuitGameInput();
}

bool dae::KeyBoard::IsKeyDownThisFrame(SDL_Scancode key) const
{
	return m_pImpl->IsKeyDownThisFrame(key);
}

bool dae::KeyBoard::IsKeyUpThisFrame(SDL_Scancode key) const
{
	return m_pImpl->IsKeyUpThisFrame(key);
}

bool dae::KeyBoard::IsKeyHeld(SDL_Scancode key) const
{
	return m_pImpl->IsKeyHeld(key);
}