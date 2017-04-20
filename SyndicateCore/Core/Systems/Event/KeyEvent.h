#ifndef KEYEVENT_H_
#define KEYEVENT_H_

#include <Common.h>

#include <unordered_map>
#include <algorithm>

#include <Interfaces/IEvent.h>
#include <Utilities/Callback.h>
#include <Systems/Input/Keys.h>

namespace Syndicate {

using namespace Utilities;

class SYNDICATE_API KeyEvent : public IEvent
{
private:
	std::unordered_map<Keys, std::vector<Callback>> m_KeyMap;

public:
	KeyEvent();

	// Keycode & callback index from Callback Utility
	void Bind(Keys keycode, Callback);
	void Unbind(Callback);

	~KeyEvent();
};

}

#endif