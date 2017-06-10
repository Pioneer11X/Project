#pragma once

#include <glad\glad.h>		// Glad must be included before anything that might use OpenGL. This contains the correct OpenGL Header files.
#include <GLFW\glfw3.h>

#include <iostream>

#include "Shader.h"

// Declaraction for the resize window function.
void framebuffer_size_callback(GLFWwindow * window, int width, int height);

// Declaration for Custom Input Processing.
void processInput(GLFWwindow * window);


int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create Window.
	GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);

	// Check if the window is created.
	if (nullptr == window) {

		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;

	}

	// Make the current glfw context , the created window.
	glfwMakeContextCurrent(window);

	// Initialise Glad.

	// glfwGetProcAddress returns the function based on the OS.
	// gladLoadGLLoader loads it up and points to the appropriate and correct OpenGL function pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to init GLAD" << std::endl;
	}

	// Set the OpenGL Viewport Size.
	glViewport(0, 0, 800, 600);

	// Point the resize function to glfw.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// build and compile our shader program
	// ------------------------------------

	Shader ourShader("simple.vs", "simple.fs");


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// Positions				// Colors
		0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f, // top right
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position Attribute.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// While the window needn't close,
	while (!glfwWindowShouldClose(window))
	{
		// Call the custom Input function every frame.
		processInput(window);

		{

			// Rendering Block.
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		
			ourShader.use();

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		
		}


		// Swap the back buffer.
		glfwSwapBuffers(window);

		// OS specific window events.
		glfwPollEvents();
	}

	// Terminate all the other things.
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
