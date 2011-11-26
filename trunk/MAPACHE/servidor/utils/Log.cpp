#include "Log.h"

Log::Log(const std::string& pathLogFile) :
	category(log4cpp::Category::getInstance(pathLogFile)) {
	std::string format = " %d:%p - %m%n";
	appender = new log4cpp::FileAppender("FileAppender", pathLogFile);
	layoutPattern = new log4cpp::PatternLayout();
	layoutPattern->setConversionPattern(format);
	appender->setLayout(layoutPattern);
//	layout = new log4cpp::SimpleLayout();
//	appender->setLayout(layout);
	category.setAppender(appender);
	category.setPriority(log4cpp::Priority::INFO);
}

//Sets the format of log lines handled by this PatternLayout.
//
//By default, set to "%m%n".
//Format characters are as follows:
//%%%% - a single percent sign
//%c - the category
//%d - the date
//
//Date format: The date format character may be followed by a date format specifier enclosed between braces. For example, %d{%H:%M:%S,%l} or %d{%d %m %Y %H:%M:%S,%l}. If no date format specifier is given then the following format is used: "Wed Jan 02 02:03:55 1980". The date format specifier admits the same syntax as the ANSI C function strftime, with 1 addition. The addition is the specifier %l for milliseconds, padded with zeros to make 3 digits.
//%m - the message
//%n - the platform specific line separator
//%p - the priority
//%r - milliseconds since this layout was created.
//%R - seconds since Jan 1, 1970
//%u - clock ticks since process start
//%x - the NDC
Log::Log(const std::string& pathLogFile, const std::string& format) :
	category(log4cpp::Category::getInstance(pathLogFile)) {
	appender = new log4cpp::FileAppender("FileAppender", pathLogFile);
	layoutPattern = new log4cpp::PatternLayout();
	layoutPattern->setConversionPattern(format);
	appender->setLayout(layoutPattern);
	category.setAppender(appender);
	category.setPriority(log4cpp::Priority::INFO);
}

Log::~Log() {
	log4cpp::Category::shutdown();
}

void Log::logWarning(const std::string& menssage) {
	category.warn(menssage);
}

void Log::logError(const std::string& menssage) {
	category.error(menssage);
}

void Log::logInfo(const std::string& menssage) {
	category.info(menssage);
}

