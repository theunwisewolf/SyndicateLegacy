#include "ISystem.h"

namespace Syndicate 
{

ISystem::ISystem(std::string sysname) :
	m_SystemName(sysname)
{
	SYNDICATE_INFO( "Initializing system " + m_SystemName + "..." );
}

ISystem::~ISystem()
{
	SYNDICATE_INFO("Deinitializing system " + m_SystemName + "...");
}

}