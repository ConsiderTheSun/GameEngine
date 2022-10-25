#include "Logger.h"

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Initialize(std::string _outFileName) {
	outFileName = _outFileName;
}