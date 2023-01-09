#include "Logger.h"
#include <iostream>
#include <windows.h>

Logger::LogMode Logger::currentMode = All;


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Logger::Info(std::string message) {
	if (currentMode < All) return;
	std::cout << "[info] " << message << std::endl;
}
void Logger::Warning(std::string message) {
	if (currentMode < ErrorWarning) return;
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << "[warning] " << message << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
}
void Logger::Error(std::string message) {
	if (currentMode < ErrorOnly) return;
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "[error] " << message << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
}
