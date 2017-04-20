#include "KeyEvent.h"

namespace Syndicate {

KeyEvent::KeyEvent()
{
}

void KeyEvent::Bind(Keys keycode, Callback callback)
{
	auto it = std::find(this->m_KeyMap[keycode].begin(), this->m_KeyMap[keycode].end(), callback);
	
	// Callback already present
	if (it != this->m_KeyMap[keycode].end())
	{
		return;
	}

	this->m_KeyMap[keycode].push_back(callback);
}

void KeyEvent::Unbind(Callback callback)
{
	for (auto keyCallbacksPair : this->m_KeyMap)
	{
		auto it = std::find(keyCallbacksPair.second.begin(), keyCallbacksPair.second.end(), callback);

		// Callback already present
		if (it != keyCallbacksPair.second.end())
		{
			keyCallbacksPair.second.erase(it);
			break;
		}
	}
}

KeyEvent::~KeyEvent()
{
	for (auto it = m_KeyMap.begin(); it != m_KeyMap.end(); it++)
	{
		it->second.clear();
	}

	this->m_KeyMap.clear();
}

}