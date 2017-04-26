#ifndef MOUSEEVENT_H_
#define MOUSEEVENT_H_

#include <Common.h>

#include <Utilities/Logger.h>

#include <unordered_map>
#include <algorithm>

#include <Interfaces/IEvent.h>
#include <Utilities/Callback.h>
#include <Systems/Input/InputMap.h>

namespace Syndicate {

using namespace Utilities;

class SYNDICATE_API MouseEvent : public IEvent
{
public:
	static MouseEvent* i();

private:
	int x;
	int y;

	bool m_ButtonDown[3];
	int m_NumButtonsDown = 0;

	std::vector<Callback> m_MouseMoveMap;
	std::unordered_map<MouseButtons, std::vector<Callback>> m_MouseUpMap;
	std::unordered_map<MouseButtons, std::vector<Callback>> m_MouseDownMap;
	std::unordered_map<MouseButtons, std::vector<Callback>> m_MousePressMap;
	MouseEvent();

public:

	void BindMouseMove(Callback callback);
	void UnbindMouseMove(Callback callback);

	void BindMouseUp(MouseButtons button, Callback callback);
	void UnbindMouseUp(Callback callback);

	void BindMouseDown(MouseButtons button, Callback callback);
	void UnbindMouseDown(Callback callback);

	void BindMousePress(MouseButtons button, Callback callback);
	void UnbindMousePress(Callback callback);

	std::vector<Callback> getMouseMoveEvents(int x, int y)							{ this->x = x; this->y = y; return this->m_MouseMoveMap; }
	std::vector<Callback> getMouseUpEvents(MouseButtons button, int x, int y)		{ this->x = x; this->y = y; return this->m_MouseUpMap[button]; }
	std::vector<Callback> getMouseDownEvents(MouseButtons button, int x, int y)		{ this->x = x; this->y = y; return this->m_MouseDownMap[button]; }
	std::vector<Callback> getMousePressEvents(MouseButtons button, int x, int y)	{ this->x = x; this->y = y; return this->m_MousePressMap[button]; }

	inline int getX() const { return x; }
	inline int getY() const { return y; }

	void setButtonDown(MouseButtons button, bool state) { 
		this->m_ButtonDown[(int)button] = state; 
		
		if (state)
			m_NumButtonsDown++;
		else
			m_NumButtonsDown--;
	}

	inline int getButtonsDown() const { return m_NumButtonsDown; }
	inline bool getButtonDown(MouseButtons button) { return this->m_ButtonDown[(int)button]; }
	inline bool* getButtonDownMap() { return this->m_ButtonDown; }

	~MouseEvent();
};

}

#endif