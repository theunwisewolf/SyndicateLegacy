#ifndef KEYEVENT_H_
#define KEYEVENT_H_

#include <Common.h>

#include <Utilities/Logger.h>

#include <unordered_map>
#include <algorithm>

#include <Interfaces/IEvent.h>
#include <Utilities/Callback.h>
#include <Systems/Input/InputMap.h>

namespace Syndicate {

using namespace Utilities;

class SYNDICATE_API KeyEvent : public IEvent
{
public:
	static KeyEvent* i();

private:
	std::unordered_map<Keys, std::vector<Callback>> m_KeyPressMap;
	std::unordered_map<Keys, std::vector<Callback>> m_KeyDownMap;
	std::unordered_map<Keys, std::vector<Callback>> m_KeyUpMap;
	KeyEvent();

public:

	// Keycode & callback index from Callback Utility
	void BindKeyDown(Keys keycode, Callback callback);
	void UnbindKeyDown(Callback);

	void BindKeyUp(Keys keycode, Callback callback);
	void UnbindKeyUp(Callback);

	void BindKeyPress(Keys keycode, Callback callback);
	void UnbindKeyPress(Callback);

	std::vector<Callback> getKeyDownEvents(Keys key) { return this->m_KeyDownMap[key]; }
	std::vector<Callback> getKeyUpEvents(Keys key) { return this->m_KeyUpMap[key]; }
	std::vector<Callback> getKeyPressEvents(Keys key) { return this->m_KeyPressMap[key]; }

	~KeyEvent();
};

}

#endif