#ifndef IEVENT_H_
#define IEVENT_H_

#include <Common.h>
#include <Systems/Event/Events.h>

namespace Syndicate {

class SYNDICATE_API IEvent
{
protected:
	Events m_Type;

protected:
	IEvent() {}
	virtual ~IEvent() {}
};

}

#endif