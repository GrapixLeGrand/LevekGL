#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "glm/glm.hpp"

namespace Levek {
class Camera {
public:

	glm::vec3 eye;
	glm::vec3 front;
	glm::vec3 up;
	float yaw, pitch, roll;

    glm::mat4 view;

	Camera(glm::vec3 eye, glm::vec3 front, glm::vec3 up);
	Camera();
	
    glm::mat4& getView() {
        return view;
    }

	void setEye(const glm::vec3& newEye) {
		this->eye.x = newEye.x;
		this->eye.y = newEye.y;
		this->eye.z = newEye.z;
	}

	void setFront(const glm::vec3& newFront) {
		this->front.x = newFront.x;
		this->front.y = newFront.y;
		this->front.z = newFront.z;
	}

	void setUp(const glm::vec3& newUp) {
		this->up.x = newUp.x;
		this->up.y = newUp.y;
		this->up.z = newUp.z;
	}

	void addEye(const glm::vec3& offset) {
		this->eye.x += offset.x;
		this->eye.y += offset.y;
		this->eye.z += offset.z;
	}

	void addFront(const glm::vec3& offset) {
		this->front.x += offset.x;
		this->front.y += offset.y;
		this->front.z += offset.z;
	}

	void addUp(const glm::vec3& offset) {
		this->up.x += offset.x;
		this->up.y += offset.y;
		this->up.z += offset.z;
	}

};
};