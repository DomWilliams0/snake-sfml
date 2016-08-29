#pragma once
#include <iostream>
#include <string>

namespace Logger
{
	enum Level { INFO, DEBUG };

	struct _Logger;

	void createLogger(std::ostream &os, Level loggingLevel);
	void logInfo(std::string msg);
	void logDebug(std::string msg);
}