/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Logger.cpp
Project: BIT_SAVER
Author: 
Creation date: 2021-03-06
-----------------------------------------------------------------*/
#include <iostream>    // cout.rdbuf
#include "Logger.h"

Logger::Logger(Logger::Severity severity, bool useConsole, std::chrono::system_clock::time_point starttime) : minLevel(severity), outStream("Trace.log"), startTime(starttime) {
	if (useConsole == true) {
		outStream.set_rdbuf(std::cout.rdbuf());
	}
}

Logger::~Logger() {
	outStream.flush();
	outStream.close();
}

void Logger::Log(Logger::Severity severity, std::string message)
{
	if (severity >= minLevel)
	{
		outStream.precision(4);
		outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";
		switch (severity)
		{
		case Severity::Verbose:
		{
			outStream << "Verb" << '\t' << message << '\n';
			break;
		}
		case Severity::Debug:
		{
			outStream << "Debug" << '\t' << message << "\n";
			break;
		}
		case Severity::Event:
		{
			outStream << "Event" << '\t' << message << "\n";
			break;
		}
		case Severity::Error:
		{
			outStream << "Error" << '\t' << message << "\n";
			break;
		}
		}
	}

}

double Logger::GetSecondsSinceStart()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double time = std::chrono::duration<double>(now - lastTick).count();
	return static_cast<double>(time);
}