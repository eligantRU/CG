#include "stdafx.h"

#include "KeyboardHandler.h"

bool CKeyboardHandler::IsKeyPressed(SDL_Keycode keycode) const
{
	return (m_keyboard.find(keycode) != m_keyboard.end());
}

void CKeyboardHandler::OnKeyDown(SDL_Keycode keycode)
{
	m_keyboard.insert(keycode);
}

void CKeyboardHandler::OnKeyUp(SDL_Keycode keycode)
{
	m_keyboard.erase(keycode);
}
