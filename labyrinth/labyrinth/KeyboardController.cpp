#include "stdafx.h"

#include "KeyboardController.h"

bool CKeyboardController::IsKeyPressed(SDL_Keycode keycode) const
{
	return (m_keyboard.find(keycode) != m_keyboard.end());
}

void CKeyboardController::OnKeyDown(SDL_Keycode keycode)
{
	m_keyboard.insert(keycode);
}

void CKeyboardController::OnKeyUp(SDL_Keycode keycode)
{
	m_keyboard.erase(keycode);
}
