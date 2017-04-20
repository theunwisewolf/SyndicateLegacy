#ifndef IGAME_H_
#define IGAME_H_

#include <Common.h>

namespace Syndicate 
{

class SYNDICATE_API IGame
{
	friend class Engine;

protected:
	virtual bool Initialize() { return true; };
	virtual bool Render() { return true; };
	virtual bool Shutdown() { return true; };
};

}

#endif