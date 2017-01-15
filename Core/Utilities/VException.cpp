#include "VException.h"

namespace Venus { namespace Utilities {

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
