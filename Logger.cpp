#pragma once
#include <iostream>
#include <string>
#include "Logger.hpp"


struct _Logger
{
	Logger::Level level;
	std::ostream *stream;

	void log(std::string msg, Logger::Level level)
	{
		std::string l;
		switch (level)
		{
		case Logger::INFO: l = "INFO";
			break;
		case Logger::DEBUG: l = "DEBUG";
			break;
		}

		(*stream) << l << ": " << msg << std::endl;

	}
};

_Logger logger;

void Logger::createLogger(std::ostream &os, Level loggingLevel)
{
	logger.stream = &os;
	logger.level = loggingLevel;
}

void Logger::logInfo(std::string msg)
{
	logger.log(msg, Level::INFO);
}

void Logger::logDebug(std::string msg)
{
	logger.log(msg, Level::DEBUG);
}
