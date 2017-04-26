#include "InputManager.h"

namespace Syndicate {

InputManager::InputManager() :
	m_MouseCoordinates(0.0f, 0.0f)
{

}

void InputManager::Initialize()
{
}

void InputManager::DispatchEvents(Events type, UINT message, WPARAM wParam, LPARAM lParam)
{
	MouseButtons button;

	switch (type)
	{
	case Events::KEYDOWN:
		this->m_KeysDown[wParam] = true;
		//EventManager::i()->DispatchEvents(KeyEvent::i()->getKeyDownEvents((Keys)wParam));
		break;

	case Events::KEYUP:
		this->m_KeysDown[wParam] = false;
		EventManager::i()->DispatchEvents(KeyEvent::i()->getKeyUpEvents((Keys)wParam));
		break;

	case Events::MOUSEMOVE:
		this->m_MouseCoordinates.x = GET_X_LPARAM(lParam);
		this->m_MouseCoordinates.y = GET_Y_LPARAM(lParam);

		EventManager::i()->DispatchEvents(MouseEvent::i()->getMouseMoveEvents(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		break;

	case Events::MOUSEDOWN:
		this->m_MouseCoordinates.x = GET_X_LPARAM(lParam);
		this->m_MouseCoordinates.y = GET_Y_LPARAM(lParam);

		button = InputManager::GetMouseButton(message);
		MouseEvent::i()->setButtonDown(button, true);

		EventManager::i()->DispatchEvents(MouseEvent::i()->getMousePressEvents(button, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		break;

	case Events::MOUSEUP:
		this->m_MouseCoordinates.x = GET_X_LPARAM(lParam);
		this->m_MouseCoordinates.y = GET_Y_LPARAM(lParam);

		button = InputManager::GetMouseButton(message);
		MouseEvent::i()->setButtonDown(button, false);

		EventManager::i()->DispatchEvents(MouseEvent::i()->getMouseUpEvents(button, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		break;
	}

	// Dispatch any KeyPress Events
	int mask = 0x40000000;
	int previousState = lParam & mask;

	// The key was previously not down, send the press signal
	if (!previousState)
	{
		EventManager::i()->DispatchEvents(KeyEvent::i()->getKeyPressEvents((Keys)wParam));
	}
}

void InputManager::Update()
{
	for (unsigned int i = 0; i < MAX_KEYS; ++i)
	{
		if (this->m_KeysDown[i])
		{
			EventManager::i()->DispatchEvents(KeyEvent::i()->getKeyDownEvents((Keys)i));
		}
	}

	if (!MouseEvent::i()->getButtonsDown())
	{
		return;
	}

	bool* map = MouseEvent::i()->getButtonDownMap();

	// One or more of the mouse buttons is down
	for (int i = 0; i < 3; ++i)
		if(map[i] == true)
			EventManager::i()->DispatchEvents(MouseEvent::i()->getMouseDownEvents((MouseButtons)i, MouseEvent::i()->getX(), MouseEvent::i()->getY()));
}

MouseButtons InputManager::GetMouseButton(UINT message)
{
	if (message == WM_LBUTTONUP || message == WM_LBUTTONDOWN)
	{
		return MouseButtons::BUTTON_LEFT;
	}

	else if(message == WM_RBUTTONUP || message == WM_RBUTTONDOWN)
	{
		return MouseButtons::BUTTON_RIGHT;
	}

	else if (message == WM_MBUTTONUP || message == WM_MBUTTONDOWN)
	{
		return MouseButtons::BUTTON_MIDDLE;
	}

	return MouseButtons::BUTTON_UNKNOWN;
}

bool InputManager::isKeyDown(Keys key)
{
	return this->m_KeysDown[(int)key];
}

bool InputManager::isKeyUp(Keys key)
{
	return this->m_KeysDown[(int)key];
}
void InputManager::ShutDown()
{

}

}