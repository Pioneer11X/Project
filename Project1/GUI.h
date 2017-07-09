#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "Imgui\imgui.h"
#include "imgui_impl_glfw_gl3.h"


class GUI
{

	static GUI instance;

private:

	GUI();

public:
	
	// Singleton reference
	static GUI& Instance()
	{
		static GUI instance;
		return instance;
	}


	void Init(GLFWwindow * window);
	bool Loop();
	void Draw();
	void End();

	~GUI();
};

