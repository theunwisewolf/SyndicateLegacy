#include "VException.h"

namespace Syndicate { namespace Utilities {

VException::VException(std::string message)
	: message{ message }
{

}

VException::VException()
{
	this->message = "Unknown exception occured.";
}

VException::~VException()
{
}

}};
