#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad\glad.h>		// Include this before everything else.

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Including them again.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:

	// Program ID.
	unsigned int ID;

	// Constructor to read and build the Shader.
	Shader(const GLchar * vertexPath, const GLchar * fragmentPath);

	// Use/Activate the Shader.
	void use();

	// Utility uniform setters.
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat(const std::string &name, glm::mat4 value) const;

	~Shader();
};


#endif // !SHADER_H