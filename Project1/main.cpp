#pragma once

#include "Engine.h"

#include <iostream>


int main()
{
	
	if (!Engine::Instance().InitSystems()) {
		return -1;
	}

	// build and compile shaders
	// -------------------------
	Shader ourShader("model.vs", "model.fs");

	// load models
	// -----------
	Model ourModel("Assets/nanosuit/nanosuit.obj");

	Scene curScene;

	Entity * test = new Entity(&ourShader, &ourModel);
	curScene.AddModel(test);

	GUI::Instance().Init(Engine::Instance().getCurrentWindow());

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(Engine::Instance().getCurrentWindow()))
	{

		GUI::Instance().Loop();

		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(Engine::Instance().getCurrentWindow());

		// render
		// ------
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		ourShader.use();

		/*
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat("projection", projection);
		ourShader.setMat("view", view);

		// render the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat("model", model);
		ourModel.Draw(ourShader);
		*/

		curScene.Draw(Engine::Instance().getCurrentCamera(), (float)SCR_WIDTH, (float)SCR_HEIGHT);

		GUI::Instance().Draw();


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(Engine::Instance().getCurrentWindow());
		glfwPollEvents();
	}

	GUI::Instance().End();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}