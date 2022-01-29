
#include "LevekGL.hpp"
#include <vector>
#include <string>

//from https://learnopengl.com/code_viewer.php?code=advanced/cubemaps_skybox_data
extern float skyboxVertices[108];

struct SkyBoxPipelineState {

	Levek::CubeMap* cubeMap;
    Levek::VertexBuffer* cubeMapVbo; //= Levek::VertexBuffer(skyboxVertices, sizeof(skyboxVertices));
    Levek::VertexBufferLayout* cubeMapLayout;// = Levek::VertexBufferLayout(); cubeMapLayout.push<glm::vec3>(1);
    Levek::VertexArray* cubeMapVa;

    Levek::Shader cubeMapShader = Levek::ShaderFactory::makeFromFile(
		SAMPLES_DIRECTORY"/resources/shaders/skybox.vert",
		SAMPLES_DIRECTORY"/resources/shaders/skybox.frag"
	);

	SkyBoxPipelineState(const std::vector<std::string>& imagePaths) {
		cubeMap = new Levek::CubeMap(imagePaths, 2048, 2048);
		cubeMapVbo = new Levek::VertexBuffer(skyboxVertices, sizeof(skyboxVertices));
    	cubeMapLayout = new Levek::VertexBufferLayout(); cubeMapLayout->push<glm::vec3>(1);
		cubeMapVa->addBuffer(cubeMapVbo, cubeMapLayout);
	}

	void draw(Levek::Renderer *renderer, glm::mat4& vp) {
		
		renderer->setDepthMask(false);
        cubeMapShader.bind();
        cubeMap->bind();
        cubeMapShader.setUniform1i("skybox", 0);
        cubeMapShader.setUniformMat4f("vp", vp);
        cubeMapShader.unbind();

        renderer->draw(cubeMapVa, &cubeMapShader);

        renderer->setDepthMask(true);
	}

	~SkyBoxPipelineState() {
		delete cubeMap;
		delete cubeMapVbo;
		delete cubeMapLayout;
		delete cubeMapVa;
	}
};

const std::vector<std::string> static getSkyBoxPaths() {

	std::vector<std::string> skyBoxImagesPaths { "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg" };
    for (auto it = skyBoxImagesPaths.begin(); it != skyBoxImagesPaths.end(); it++) {
        (*it) = SAMPLES_DIRECTORY"/resources/skybox/" + (*it);
    }

	return skyBoxImagesPaths;
}

void static UpdateCameraPositionWASD(Levek::InputController* inputController, Levek::Camera& camera, float dt, float speed) {
    
    glm::vec3 positionOffset = glm::vec3(0.0);
	const float cameraSpeed = speed * dt;

	if (inputController->isKeyPressed(Levek::LEVEK_KEY_W)) {
		positionOffset += cameraSpeed * camera.front;
	}
	if (inputController->isKeyPressed(Levek::LEVEK_KEY_S)) {
		positionOffset += -cameraSpeed * camera.front;
    }
	if (inputController->isKeyPressed(Levek::LEVEK_KEY_A)) {
		positionOffset += glm::normalize(glm::cross(camera.front, camera.up)) * -cameraSpeed;
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
    //&& !ImGui::IsItemHovered() && !ImGui::IsWindowHovered()
	if (inputController->isLeftMouseButtonPressed()) {

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