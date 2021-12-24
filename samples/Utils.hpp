
#include "LevekGL.hpp"

void static UpdateCameraPositionWASD(Levek::InputController* inputController, Levek::Camera& camera, float dt, float speed) {
    
    glm::vec3 positionOffset = glm::vec3(0.0);
	const float cameraSpeed = speed * dt;
    inputController->isKeyPressed(Levek::LEVEK_KEY_W);

	if (inputController->isKeyPressed(Levek::LEVEK_KEY_W)) {
		positionOffset += cameraSpeed * camera.front;
	}
	if (inputController->isKeyPressed(Levek::LEVEK_KEY_S)) {
		positionOffset += -cameraSpeed * camera.front;
    }
	if (inputController->isKeyPressed(Levek::LEVEK_KEY_A)) {
		positionOffset += glm::normalize(glm::cross(camera.front, camera.up)) * - cameraSpeed;
    }
	if (inputController->isKeyPressed(Levek::LEVEK_KEY_D)) {
		positionOffset += glm::normalize(glm::cross(camera.front, camera.up)) * cameraSpeed;
    }
	camera.addEye(positionOffset);
}

extern float lastMouseValueX;
extern float lastMouseValueY;
extern bool wasLeftButtonPressed;

static void UpdateCameraWithMouseOnDrag(Levek::InputController* inputController, Levek::Camera& camera, float sensivity) {

	float mouseX = inputController->getMouseX();
	float mouseY = inputController->getMouseY();
	if (inputController->isLeftMouseButtonPressed() && !ImGui::IsItemHovered() && !ImGui::IsWindowHovered()) {

		if (!wasLeftButtonPressed) {
			lastMouseValueX = mouseX;
			lastMouseValueY = mouseY;
			wasLeftButtonPressed = true;
		}

		float offsetX = (mouseX - lastMouseValueX) * sensivity;
		float offsetY = (lastMouseValueY - mouseY) * sensivity;
		lastMouseValueX = mouseX;
		lastMouseValueY = mouseY;

		camera.yaw += offsetX;
		camera.pitch += offsetY;

		if (camera.pitch > 89.0f) {
			camera.pitch = 89.0f;
		}
		if (camera.pitch < -89.0f) {
			camera.pitch = -89.0f;
		}

		glm::vec3 direction;
		direction.z = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
		direction.y = sin(glm::radians(camera.pitch));
		direction.x = sin(glm::radians(-camera.yaw)) * cos(glm::radians(camera.pitch));
		camera.setFront(glm::normalize(direction));

	} else {
		wasLeftButtonPressed = false;
	}

	/*
	if (this->isMouseDragging || this->mouseCursorDisabled) {
		if (this->firstMouseAction) {
			this->lastX = (float)xpos;
			this->lastY = (float)ypos;
			this->firstMouseAction = false;
		}
		float xoffset = (float)xpos - this->lastX;
		float yoffset = this->lastY - (float)ypos;
		//std::cout << xoffset << " " << yoffset << std::endl;
		this->lastX = (float)xpos;
		this->lastY = (float)ypos;
		this->lastOffsetX = xoffset;
		this->lastOffsetY = yoffset;
		float sensitivity = 0.2f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		yaw += xoffset;
		pitch += yoffset;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		target = glm::normalize(direction);
	//}
	*/
}