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
	// Shader ourShader("model.vs", "model.fs");
	Shader ourShader("model.vs", "model_grayscale.fs");

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
	Engine::Instance().Run(curScene);

	GUI::Instance().End();

	Engine::Instance().CloseSystems();

	return 0;
}