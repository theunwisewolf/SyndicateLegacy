#include "EventManager.h"

namespace Syndicate {

EventManager* EventManager::i()
{
	static EventManager instance;
	return &instance;
}

EventManager::EventManager() :
	m_Done(false)
{

}

void EventManager::Initialize()
{

}

void EventManager::DispatchEvent(Events type)
{
	for (auto event : m_QuickEvents[type])
	{
		event();
	}

	for (auto callbackHandler : m_Events[type])
	{
		callbackHandler.getCallback()();
	}
}

void EventManager::DispatchEvents(const std::vector<Callback>& callbacks)
{
	for (auto callbackHandler : callbacks)
	{
		callbackHandler.getCallback()();
	}
}

unsigned int EventManager::AddEvent(Events type, std::function<void ()> callback)
{
	m_QuickEvents[type].push_back(callback);

	return m_QuickEvents[type].size() - 1;
}

void EventManager::AddEvent(Events type, const Callback& callback)
{
	m_Events[type].push_back(callback);
}

void EventManager::RemoveEvent(Events type, const Callback& callback)
{
	auto it = std::find(m_Events[type].begin(), m_Events[type].end(), callback);

	// Not found
	if (it == m_Events[type].end())
	{
		return;
	}

	m_Events[type].erase(it);
}


void EventManager::RemoveEvent(Events type, int index)
{
	if (index < m_QuickEvents[type].size())
	{
		m_QuickEvents[type].erase(m_QuickEvents[type].begin() + index);
	}
}

void EventManager::ShutDown()
{
	if (this->m_Done)
		return;

	for (auto it = m_QuickEvents.begin(); it != m_QuickEvents.end(); it++)
	{
		it->second.clear();
	}

	for (auto it = m_Events.begin(); it != m_Events.end(); it++)
	{
		it->second.clear();
	}

	m_QuickEvents.clear();
	m_Events.clear();
	m_Done = true;
}

EventManager::~EventManager()
{
	this->ShutDown();
}

}