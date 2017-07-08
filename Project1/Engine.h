#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.h"
#include "GUI.h"

#include <vector>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Mouse Buttons.
bool mouseLeftClicked = false;

// Camera and Mouse Interaction
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);


class Engine {

	static Engine instance;

private:

	Engine() {

	}

	// Variables for the Engine and the Window.

	GLFWwindow * _engineCurrentWindow;
	
	bool ShouldClose;
	

public:

	Camera _currentCamera;

	static Engine& Instance() {
		static Engine instance;
		return instance;
	}

	bool InitSystems() {

		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

		InitCamera();

		// glfw window creation
		// --------------------
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		// tell GLFW to capture our mouse
		// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);

		_engineCurrentWindow = window;

		return true;

	}

	void Run(Scene _scene) {

		while ( !glfwWindowShouldClose(Engine::Instance().getCurrentWindow()) )
		{
			// TODO: Change this to per scene basis.. much later into the Engine Dev.
			GUI::Instance().Loop();

			processInput(Engine::Instance().getCurrentWindow());

			// render
			// ------
			glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			_scene.Draw(getCurrentCamera(), SCR_WIDTH, SCR_HEIGHT);

			GUI::Instance().Draw();

			glfwSwapBuffers(Engine::Instance().getCurrentWindow());
			glfwPollEvents();

		}
			

	}

	void InitCamera() {
		// camera
		Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

		Instance()._currentCamera = camera;
	}

	void CloseSystems() {
		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
	}


	GLFWwindow * getCurrentWindow() {
		return _engineCurrentWindow;
	}

	Camera getCurrentCamera() {
		return _currentCamera;
	}

	void setCamera(Camera _camera) {
		_currentCamera = _camera;
	}

};

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{

	Camera camera = Engine::Instance().getCurrentCamera();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Engine::Instance()._currentCamera.ProcessKeyboard(FORWARD, deltaTime);
		camera.ProcessKeyboard(FORWARD, deltaTime);
		std::cout << "DSFJh" << std::endl;
	}
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	Engine::Instance().setCamera(camera);
}

void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	if (GLFW_MOUSE_BUTTON_1 == button && GLFW_PRESS == action) {
		mouseLeftClicked = true;
	}
	else if (GLFW_MOUSE_BUTTON_1 == button && GLFW_RELEASE == action) {
		mouseLeftClicked = false;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	if (mouseLeftClicked == true) {

		// This should only execute when the mouse left is clicked.
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		Engine::Instance().getCurrentCamera().ProcessMouseMovement(xoffset, yoffset);

	}
	else {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}


}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Engine::Instance().getCurrentCamera().ProcessMouseScroll(yoffset);
}