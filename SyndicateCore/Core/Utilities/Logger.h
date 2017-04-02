#ifndef LOGGER_H_
#define LOGGER_H_

#include <Common.h>

#include <string>
#include <iostream>
#include <iomanip>

#if defined(WIN32) | defined(_WIN32)
#include <Windows.h>

#define CONSOLE_COLOR_GREEN		0x0A
#define CONSOLE_COLOR_BLUE		0x0B
#define CONSOLE_COLOR_RED		0x0C
#define CONSOLE_COLOR_YELLOW	0x0E
#define CONSOLE_COLOR_WHITE		0x0F

#define SET_CONSOLE_TEXT_COLOR(color) SetConsoleTextAttribute(hConsole, color);
#define RESET_CONSOLE_TEXT_COLOR() SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_WHITE);

#endif

#define SYNDICATE_INFO(message)				Syndicate::Utilities::Logger::logError(message, Syndicate::Utilities::Logger::MessageTypes::SYNDICATE_INFO_MESSAGE)
#define SYNDICATE_SUCCESS(message)			Syndicate::Utilities::Logger::logError(message, Syndicate::Utilities::Logger::MessageTypes::SYNDICATE_SUCCESS_MESSAGE)
#define SYNDICATE_WARNING(message)			Syndicate::Utilities::Logger::logError(message, Syndicate::Utilities::Logger::MessageTypes::SYNDICATE_WARNING_MESSAGE)
#define SYNDICATE_ERROR(message)			Syndicate::Utilities::Logger::logError(message, Syndicate::Utilities::Logger::MessageTypes::SYNDICATE_ERROR_MESSAGE)

#define SYNDICATE_INFO_NH(message)			Syndicate::Utilities::Logger::logError(message, Syndicate::Utilities::Logger::MessageTypes::SYNDICATE_INFO_MESSAGE, false)
#define SYNDICATE_SUCCESS_NH(message)		Syndicate::Utilities::Logger::logError(message, Syndicate::Utilities::Logger::MessageTypes::SYNDICATE_SUCCESS_MESSAGE, false)
#define SYNDICATE_WARNING_NH(message)		Syndicate::Utilities::Logger::logError(message, Syndicate::Utilities::Logger::MessageTypes::SYNDICATE_WARNING_MESSAGE, false)
#define SYNDICATE_ERROR_NH(message)			Syndicate::Utilities::Logger::logError(message, Syndicate::Utilities::Logger::MessageTypes::SYNDICATE_ERROR_MESSAGE, false)

namespace Syndicate { namespace Utilities {

class SYNDICATE_API Logger 
{
public:
	enum class MessageTypes { SYNDICATE_INFO_MESSAGE, SYNDICATE_SUCCESS_MESSAGE, SYNDICATE_WARNING_MESSAGE, SYNDICATE_ERROR_MESSAGE };

private:
	static std::string m_Message;
	static MessageTypes m_MessageType;

public:
	static void logError(const std::string& message, Logger::MessageTypes messageType, bool printHeader = true);
};

}}

#endif