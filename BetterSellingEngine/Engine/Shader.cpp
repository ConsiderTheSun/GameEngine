#include "Shader.h"


Shader::Shader(const char* vertPath, const char* fragPath)
{
	std::string vertString;
	std::string fragString;

	

	std::ifstream shaderFile;
	std::stringstream vertStream, fragStream;
	try{
		// reads vertex code from file
		shaderFile.open(vertPath);
		vertStream << shaderFile.rdbuf();
		shaderFile.close();
		vertString = vertStream.str();

		// reads fragment code from file
		shaderFile.open(fragPath);
		fragStream << shaderFile.rdbuf();
		shaderFile.close();
		fragString = fragStream.str();

	}
	catch (std::ifstream::failure& e)
	{
		std::cerr << "Error: couldn't read file: " << e.what() << std::endl;
	}
	// creates the vertex shader
	const char* vertexCode = vertString.c_str();

	unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertexCode, NULL);
	glCompileShader(vertShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		std::cerr << "Error: vertex shader compilation failed\n" << infoLog << std::endl;
	}

	// creates the fragment shader
	const char* fragCode = fragString.c_str();

	unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragCode, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cerr << "Error: fragment shader compilation failed\n" << infoLog << std::endl;
	}

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertShader);
	glAttachShader(shaderID, fragShader);
	glLinkProgram(shaderID);
	// check for linking errors
	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
		std::cerr << "Error: shader linking failed\n" << infoLog << std::endl;
	}
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

}


void Shader::Use() {
	glUseProgram(shaderID);
}



void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, const int value) const {
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const float* value) const {
	glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}