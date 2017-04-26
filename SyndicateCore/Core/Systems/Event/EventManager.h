#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include <Common.h>

#include <map>
#include <vector>
#include <algorithm>
#include <functional>

#include <Systems/Event/Events.h>
#include <Utilities/Callback.h>

namespace Syndicate {

using namespace Utilities;

class SYNDICATE_API EventManager
{
private: 
	bool m_Done;

	std::map<Events, std::vector<std::function<void()>>> m_QuickEvents;
	std::map<Events, std::vector<Callback>> m_Events;

	EventManager();
	EventManager(EventManager& copy) = delete;
	EventManager& operator=(const EventManager& copy) = delete;

public:
	static EventManager* i();
	
	void Initialize();
	void ShutDown();
	unsigned int AddEvent(Events type, std::function<void ()> callback);
	void AddEvent(Events type, const Callback& callback);

	void RemoveEvent(Events type, int index);
	void RemoveEvent(Events type, const Callback& callback);
	void DispatchEvent(Events type);
	void DispatchEvents(const std::vector<Callback>& callbacks);

	~EventManager();
};

}

#endif