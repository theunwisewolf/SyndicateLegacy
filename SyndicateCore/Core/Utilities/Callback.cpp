#include "Callback.h"

namespace Syndicate { namespace Utilities {

int Callback::m_NumCallbacks = 0;

Callback::Callback(std::function<void()> function)
{
	this->m_Callback = function;

	Callback::m_NumCallbacks++;

	this->m_CallbackId = m_NumCallbacks - 1;
}

bool Callback::operator==(const Callback& left)
{
	if (left.getId() == this->getId())
	{
		return true;
	}

	return false;
}

} }