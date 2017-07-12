#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Shader.h"
#include "Model.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>

class Entity {

public:

	// An entity should contain a model, a shader and transformation stuff.
	Shader * shader;
	Model * model;
	std::map<std::string, Shader *> allShaders;

	Entity(Shader * _shader, Model * _model) {
		shader = _shader;
		model = _model;
	}

	// The map should contain a default shader.
	Entity(std::map<std::string, Shader *> _shaders, Model * _model) {
		allShaders = _shaders;
		model = _model;
		shader = _shaders.at("default"); // Note: This is mandatory.
	}

	void Draw(Camera _camera, float SCR_WIDTH, float SCR_HEIGHT) {

		// don't forget to enable shader before setting uniforms
		shader->use();
		
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(_camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = _camera.GetViewMatrix();
		shader->setMat("projection", projection);
		shader->setMat("view", view);

		// render the loaded model
		glm::mat4 modelMat;
		modelMat = glm::translate(modelMat, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		modelMat = glm::scale(modelMat, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		shader->setMat("model", modelMat);
		model->Draw(*shader);

	}

	~Entity() {

	}

};

#endif // !ENTITY_H
