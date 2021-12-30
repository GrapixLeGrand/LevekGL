#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Levek {

/**
 * @brief Base camera class
 */
class Camera {
public:

	glm::vec3 eye;
	glm::vec3 front;
	glm::vec3 up;
	float yaw, pitch, roll;

    glm::mat4 view = glm::mat4(1.0);
    glm::mat3 normalView = glm::mat3(1.0);

	Camera(glm::vec3 eye, glm::vec3 front, glm::vec3 up);
	Camera();

    virtual glm::mat4& getProjection() = 0;

    glm::mat4& getView() {
        view = glm::lookAt(eye, eye + front, up);
        return view;
    }

    glm::mat3& getNormalView() {
        normalView = glm::inverse(glm::transpose(getView()));
        return normalView;
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

	const glm::vec3& getEye() const {
		return this->eye;
	}

	const glm::vec3& getFront() const {
		return this->front;
	}

	const glm::vec3& getUp() const {
		return this->up;
	}

};
};