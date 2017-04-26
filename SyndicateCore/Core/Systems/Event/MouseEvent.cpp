#include "MouseEvent.h"

namespace Syndicate {

MouseEvent* MouseEvent::i()
{
	static MouseEvent instance;
	return &instance;
}

MouseEvent::MouseEvent()
{

}

void MouseEvent::BindMouseMove(Callback callback)
{
	auto it = std::find(this->m_MouseMoveMap.begin(), this->m_MouseMoveMap.end(), callback);

	if (it != this->m_MouseMoveMap.end())
	{
		return;
	}

	this->m_MouseMoveMap.push_back(callback);
}

void MouseEvent::UnbindMouseMove(Callback callback)
{
	auto it = std::find(this->m_MouseMoveMap.begin(), this->m_MouseMoveMap.end(), callback);

	if(it != this->m_MouseMoveMap.end())
	{
		this->m_MouseMoveMap.erase(it);
	}
}

void MouseEvent::BindMouseUp(MouseButtons button, Callback callback)
{
	auto it = std::find(this->m_MouseUpMap[button].begin(), this->m_MouseUpMap[button].end(), callback);

	// Already present
	if (it != this->m_MouseUpMap[button].end())
	{
		return;
	}

	this->m_MouseUpMap[button].push_back(callback);
}

void MouseEvent::UnbindMouseUp(Callback callback)
{
	for (auto keyCallbacksPair : this->m_MouseUpMap)
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


void MouseEvent::BindMouseDown(MouseButtons button, Callback callback)
{
	auto it = std::find(this->m_MouseDownMap[button].begin(), this->m_MouseDownMap[button].end(), callback);

	// Already present
	if (it != this->m_MouseDownMap[button].end())
	{
		return;
	}

	this->m_MouseDownMap[button].push_back(callback);
}

void MouseEvent::UnbindMouseDown(Callback callback)
{
	for (auto keyCallbacksPair : this->m_MouseDownMap)
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

void MouseEvent::BindMousePress(MouseButtons button, Callback callback)
{
	auto it = std::find(this->m_MousePressMap[button].begin(), this->m_MousePressMap[button].end(), callback);

	// Already present
	if (it != this->m_MousePressMap[button].end())
	{
		return;
	}

	this->m_MousePressMap[button].push_back(callback);
}

void MouseEvent::UnbindMousePress(Callback callback)
{
	for (auto keyCallbacksPair : this->m_MousePressMap)
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

MouseEvent::~MouseEvent()
{
	for (auto it : this->m_MouseUpMap)
	{
		it.second.clear();
	}

	for (auto it : this->m_MouseDownMap)
	{
		it.second.clear();
	}

	for (auto it : this->m_MousePressMap)
	{
		it.second.clear();
	}

	this->m_MouseUpMap.clear();
	this->m_MouseMoveMap.clear();
	this->m_MouseDownMap.clear();
	this->m_MousePressMap.clear();
}


}