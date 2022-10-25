#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm/gtc/type_ptr.hpp>
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void Use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;

	void setVec3(const std::string& name, const float* value) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
	unsigned int shaderID;
};

