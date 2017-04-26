#include "KeyEvent.h"

namespace Syndicate {

KeyEvent* KeyEvent::i()
{
	static KeyEvent instance;
	return &instance;
}

KeyEvent::KeyEvent()
{
}

void KeyEvent::BindKeyDown(Keys keycode, Callback callback)
{
	auto it = std::find(this->m_KeyDownMap[keycode].begin(), this->m_KeyDownMap[keycode].end(), callback);
	
	// Callback already present
	if (it != this->m_KeyDownMap[keycode].end())
	{
		SYNDICATE_WARNING("Trying to bind the same event twice!");
		return;
	}

	this->m_KeyDownMap[keycode].push_back(callback);
}

void KeyEvent::UnbindKeyDown(Callback callback)
{
	for (auto keyCallbacksPair : this->m_KeyDownMap)
	{
		auto it = std::find(keyCallbacksPair.second.begin(), keyCallbacksPair.second.end(), callback);

		// Callback found
		if (it != keyCallbacksPair.second.end())
		{
			keyCallbacksPair.second.erase(it);
			break;
		}
	}
}

void KeyEvent::BindKeyUp(Keys keycode, Callback callback)
{
	auto it = std::find(this->m_KeyUpMap[keycode].begin(), this->m_KeyUpMap[keycode].end(), callback);

	// Callback already present
	if (it != this->m_KeyUpMap[keycode].end())
	{
		SYNDICATE_WARNING("Trying to bind the same event twice!");
		return;
	}

	this->m_KeyUpMap[keycode].push_back(callback);
}

void KeyEvent::UnbindKeyUp(Callback callback)
{
	for (auto keyCallbacksPair : this->m_KeyUpMap)
	{
		auto it = std::find(keyCallbacksPair.second.begin(), keyCallbacksPair.second.end(), callback);

		// Callback found
		if (it != keyCallbacksPair.second.end())
		{
			keyCallbacksPair.second.erase(it);
			break;
		}
	}
}

void KeyEvent::BindKeyPress(Keys keycode, Callback callback)
{
	auto it = std::find(this->m_KeyPressMap[keycode].begin(), this->m_KeyPressMap[keycode].end(), callback);

	// Callback already present
	if (it != this->m_KeyPressMap[keycode].end())
	{
		SYNDICATE_WARNING("Trying to bind the same event twice!");
		return;
	}

	this->m_KeyPressMap[keycode].push_back(callback);
}

void KeyEvent::UnbindKeyPress(Callback callback)
{
	for (auto keyCallbacksPair : this->m_KeyPressMap)
	{
		auto it = std::find(keyCallbacksPair.second.begin(), keyCallbacksPair.second.end(), callback);

		// Callback found
		if (it != keyCallbacksPair.second.end())
		{
			keyCallbacksPair.second.erase(it);
			break;
		}
	}
}

KeyEvent::~KeyEvent()
{
	for (auto it = m_KeyUpMap.begin(); it != m_KeyUpMap.end(); it++)
	{
		it->second.clear();
	}

	for (auto it = m_KeyDownMap.begin(); it != m_KeyDownMap.end(); it++)
	{
		it->second.clear();
	}

	for (auto it = m_KeyPressMap.begin(); it != m_KeyPressMap.end(); it++)
	{
		it->second.clear();
	}

	this->m_KeyUpMap.clear();
	this->m_KeyDownMap.clear();
	this->m_KeyPressMap.clear();
}

}