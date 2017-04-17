#pragma once

#include <unordered_set>

class CKeyboardController
{
public:
	CKeyboardController() = default;
	~CKeyboardController() = default;

	bool IsKeyPressed(SDL_Keycode keycode) const;
	void OnKeyDown(SDL_Keycode keycode);
	void OnKeyUp(SDL_Keycode keycode);

private:
	std::unordered_set<SDL_Keycode> m_keyboard;
};
