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

	glm::vec3 mEye;
	glm::vec3 mFront;
	glm::vec3 mUp;
	float mYaw, mPitch, mRoll;

    glm::mat4 mView = glm::mat4(1.0);
    glm::mat3 mNormalView = glm::mat3(1.0);

	Camera(glm::vec3 eye, glm::vec3 front, glm::vec3 up);
	Camera();

    virtual glm::mat4& getProjection() = 0;

    glm::mat4& getView() {
        mView = glm::lookAt(mEye, mEye + mFront, mUp);
        return mView;
    }

    glm::mat3& getNormalView() {
        mNormalView = glm::inverse(glm::transpose(getView()));
        return mNormalView;
    }

	void setEye(const glm::vec3& newEye) {
		this->mEye.x = newEye.x;
		this->mEye.y = newEye.y;
		this->mEye.z = newEye.z;
	}

	void setFront(const glm::vec3& newFront) {
		this->mFront.x = newFront.x;
		this->mFront.y = newFront.y;
		this->mFront.z = newFront.z;
	}

	void setUp(const glm::vec3& newUp) {
		this->mUp.x = newUp.x;
		this->mUp.y = newUp.y;
		this->mUp.z = newUp.z;
	}

	void addEye(const glm::vec3& offset) {
		this->mEye.x += offset.x;
		this->mEye.y += offset.y;
		this->mEye.z += offset.z;
	}

	void addFront(const glm::vec3& offset) {
		this->mFront.x += offset.x;
		this->mFront.y += offset.y;
		this->mFront.z += offset.z;
	}

	void addUp(const glm::vec3& offset) {
		this->mUp.x += offset.x;
		this->mUp.y += offset.y;
		this->mUp.z += offset.z;
	}

	const glm::vec3& getEye() const {
		return this->mEye;
	}

	const glm::vec3& getFront() const {
		return this->mFront;
	}

	const glm::vec3& getUp() const {
		return this->mUp;
	}

	float getPitch() const {
		return mPitch;
	}

	float getYaw() const {
		return mYaw;
	}

	float getRoll() const {
		return mRoll;
	}

};
};