#pragma once
#include <memory>
#include <SDL_Scancode.h>
namespace dae
{
	class KeyBoard
	{
	public:
		KeyBoard();
		~KeyBoard();

		KeyBoard(const KeyBoard& other) = delete;
		KeyBoard(KeyBoard&& other) = delete;
		KeyBoard& operator=(const KeyBoard& other) = delete;
		KeyBoard& operator=(KeyBoard&& other) = delete;

		void Update(float deltaTime);
		bool ProcessQuitGameInput() const;

		bool IsKeyDownThisFrame(SDL_Scancode key) const;
		bool IsKeyUpThisFrame(SDL_Scancode key) const;
		bool IsKeyHeld(SDL_Scancode key) const;

	private:
		class KeyBoardImpl;
		std::unique_ptr<KeyBoardImpl> m_pImpl;
	};
}