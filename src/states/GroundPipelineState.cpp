#include "GroundPipelineState.hpp"
#include "../utils/Utils.hpp"
namespace Levek {

	GroundPipelineState::GroundPipelineState(ModelLoader* modelLoader, float scale) {
        
        this->scale = scale;
        this->scaleInv = 1.0f / scale;
        model = glm::mat4(scale);
        model[3][3] = 1.0f;
        printMat4(model);

		planeModel = modelLoader->loadFromFile(RESOURCES_DIRECTORY"/models/plane.obj");
		planeMesh = planeModel->getMesh(0);

		planeVBO = new VertexBuffer(planeMesh);
    	planeIBO = new IndexBuffer(planeMesh);
		planeIBO->bind();
		planeIBO->unbind();
		planeLayout.push<glm::vec3>(1);
    	planeLayout.push<glm::vec2>(1);
    	planeLayout.push<glm::vec3>(1);

		planeVA = new VertexArray();
		planeVA->addBuffer(planeVBO, &planeLayout);

		unitTexture.update(RESOURCES_DIRECTORY"/textures/unit.png");
		//Texture* unitTexture = new Texture(LUSTRINE_EXPERIMENTS_DIRECTORY"/resources/unit.png");
    	unitTexture.set(TextureParameters::TextureWrapMode::REPEAT);
    	unitTexture.set(TextureParameters::TextureLODFunction::LINEAR, TextureParameters::TextureLODFunction::LINEAR);

        planeShader = ShaderFactory::makeFromFile(
            RESOURCES_DIRECTORY"/shaders/ground.vert",
            RESOURCES_DIRECTORY"/shaders/ground.frag"
        );
	}


}