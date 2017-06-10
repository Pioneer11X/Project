#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad\glad.h>		// Include this before everything else.

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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

	~Shader();
};


#endif // !SHADER_H