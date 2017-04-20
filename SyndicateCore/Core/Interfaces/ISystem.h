#ifndef ISYSTEM_H_
#define ISYSTEM_H_

#include <Common.h>
#include <Utilities/Logger.h>

namespace Syndicate {

class SYNDICATE_API ISystem
{
private:
	std::string m_SystemName;

public:
	ISystem(std::string sysname);
	virtual ~ISystem();

	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual bool ShutDown() = 0;
};

}

#endif