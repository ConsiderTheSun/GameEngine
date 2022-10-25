#pragma once

#include <string>
class Logger
{
public:
	Logger();
	~Logger();

	void Initialize(std::string _outFileName);
private:
	std::string outFileName;
};

