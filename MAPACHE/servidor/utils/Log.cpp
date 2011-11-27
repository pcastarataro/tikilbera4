#include "Log.h"

Log::Log(const std::string& pathLogFile) :
	category(log4cpp::Category::getInstance(pathLogFile)) {
	std::string format = " %d:%p - %m%n";
	appender = new log4cpp::FileAppender("FileAppender", pathLogFile);
	layoutPattern = new log4cpp::PatternLayout();
	layoutPattern->setConversionPattern(format);
	appender->setLayout(layoutPattern);
	category.setAppender(appender);
	category.setPriority(log4cpp::Priority::INFO);
}

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

