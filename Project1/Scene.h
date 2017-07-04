/*

A scene class should be the current level containing all the values, that if you load a scene, you'd see this stuff on screen.

*/

#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Shader.h"
#include "Model.h"
#include "Camera.h"

#include <vector>

class Scene
{
public:

	// TODO: Change the variables to private later on.
	std::vector<Model * > models;

	Scene() {

	}

	void AddModel(Model * newModel) {
		models.push_back(newModel);
	}

	void Draw() {

	}

	~Scene() {
		// TODO: Delete the models in the vector.
	}
};

#endif // !SCENE_H