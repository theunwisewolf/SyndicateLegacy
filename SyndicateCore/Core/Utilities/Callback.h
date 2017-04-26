#ifndef CALLBACK_H_
#define CALLBACK_H_

#include <Common.h>

#include <vector>
#include <functional>

namespace Syndicate { namespace Utilities {

class SYNDICATE_API Callback 
{
private:
	static int m_NumCallbacks;
	
	int m_CallbackId;

	std::function <void()> m_Callback;

public:
	Callback(std::function<void()> function);

	bool operator==(const Callback& left);

	inline int getId() const { return this->m_CallbackId; }
	inline std::function <void()> getCallback() const { return this->m_Callback; }
};

} }

#endif