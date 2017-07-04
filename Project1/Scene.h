/*

A scene class should be the current level containing all the values, that if you load a scene, you'd see this stuff on screen.

*/

#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Entity.h"

#include <vector>

class Scene
{
public:

	// TODO: Change the variables to private later on.
	std::vector<Entity * > entities;

	Scene() {

	}

	void AddModel(Entity * newEntity) {
		entities.push_back(newEntity);
	}

	void Draw(Camera camera, float SCR_WIDTH, float SCR_HEIGHT) {
		for (std::vector<Entity *>::iterator it = entities.begin(); it != entities.end(); it++) {
			(*it)->Draw(camera, SCR_WIDTH, SCR_HEIGHT);
		}
	}

	~Scene() {
		// TODO: Delete the models in the vector.
	}
};

#endif // !SCENE_H