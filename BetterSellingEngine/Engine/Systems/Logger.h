#pragma once

#include <string>

class Logger
{
public:
	enum LogMode{Silent, ErrorOnly, ErrorWarning, All};
	Logger(){};
	
	static void SetMode(LogMode newMode) { currentMode = newMode; }

	static void Info(std::string message);
	static void Warning(std::string message);
	static void Error(std::string message);
private:

	static LogMode currentMode;

};

