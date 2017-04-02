#include "Logger.h"

namespace Syndicate { namespace Utilities {

std::string Logger::m_Message;
Logger::MessageTypes Logger::m_MessageType;

void Logger::logError(const std::string& message, Logger::MessageTypes messageType, bool printHeader)
{
	m_Message = message;
	m_MessageType = messageType;

#if defined(WIN32) | defined(_WIN32)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	switch (m_MessageType)
	{
	case MessageTypes::SYNDICATE_INFO_MESSAGE:
		SET_CONSOLE_TEXT_COLOR(CONSOLE_COLOR_BLUE);

		if(printHeader)
			m_Message = "[INFO] " + m_Message;
		break;
	case MessageTypes::SYNDICATE_SUCCESS_MESSAGE:
		SET_CONSOLE_TEXT_COLOR(CONSOLE_COLOR_GREEN);

		if (printHeader)
			m_Message = "[SUCCESS] " + m_Message;
		break;
	case MessageTypes::SYNDICATE_WARNING_MESSAGE:
		SET_CONSOLE_TEXT_COLOR(CONSOLE_COLOR_YELLOW);

		if (printHeader)
			m_Message = "[WARNING] " + m_Message;
		break;
	case MessageTypes::SYNDICATE_ERROR_MESSAGE:
		SET_CONSOLE_TEXT_COLOR(CONSOLE_COLOR_RED);

		if (printHeader)
			m_Message = "[ERROR] " + m_Message;
		break;
	}
	
	std::cout << m_Message << std::endl;
	RESET_CONSOLE_TEXT_COLOR()
}

}}

