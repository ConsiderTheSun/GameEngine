#include "2dTesting/2dTesting.h"
#include "3dTesting/3dTesting.h"
#include "AwesomeGame/AwesomeGame.h"

int main() {
	std::string d = "";
	std::cout << "Choose Game:\n";
	std::cout << "1: This Is A Game (tm)\n";
	std::cout << "2: 2dTesting\n";
	std::cout << "3: 3dTesting \n";
	std::cout << "Enter: ";
	

	std::cin >> d;
	if (d == "2") {
		TwoDTesting instance;
		instance.Setup();
		instance.Start();
	}
	else if (d == "3") {
		ThreeDTesting instance;
		instance.Setup();
		instance.Start();
	}
	else if (d == "1") {
		AwesomeGame instance;
		instance.Setup();
		instance.Start();
	}
	
}