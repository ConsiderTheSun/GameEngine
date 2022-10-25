#pragma once
#ifndef MATERIALH
#define MATERIALH



#include <glad/glad.h>


#include <iostream>
#include <string>

class Material {
public:
	Material(const char* texPath, bool noAlpha = false);
	const unsigned int GetID() { return texID; } const
	bool InitializationError(){ return initializationError; }
private:
	unsigned int texID;
	bool initializationError=true;
}; 
#endif