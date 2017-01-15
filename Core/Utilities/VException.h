#ifndef VEXCEPTION_H_
#define VEXCEPTION_H_

#include <exception>
#include <string>

namespace Venus { namespace Utilities {

class VException : public std::exception
{
public:
	std::string message;
	virtual const char* what() const throw()
	{
		return this->message.c_str();
	}

	VException();
	VException(std::string message);
	~VException();
};

}};

#endif