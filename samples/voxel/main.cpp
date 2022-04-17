#include <iostream>

#include "LevekGL.hpp"
#include "../Utils.hpp"
#include "glm/gtc/quaternion.hpp"


struct MeshPipelineState {
    Levek::Transform transform;
    Levek::VertexArray* va = nullptr;
    Levek::VertexBuffer* vb = nullptr;
    Levek::IndexBuffer* ib = nullptr;
    glm::mat4 model = glm::mat4(1.0); 
};

void initMeshPipelineState(MeshPipelineState* state, const Levek::Mesh* mesh, const Levek::Transform* transform) {

    state->vb = new Levek::VertexBuffer(mesh);
    state->ib = new Levek::IndexBuffer(mesh);
    state->va = new Levek::VertexArray();

    Levek::VertexBufferLayout layout = Levek::VertexBufferLayout();

    layout.push<glm::vec3>(1);
    layout.push<glm::vec2>(1);
    layout.push<glm::vec3>(1);

    state->va->addBuffer(state->vb, &layout);

    state->vb->unbind();
    state->ib->unbind();
    state->va->unbind();

    state->transform = *transform;

    //Levek::printMat4(state->model);
    state->model = glm::translate(state->model, transform->position);
    //Levek::printMat4(state->model);
    state->model *= glm::mat4_cast(transform->rotation);
    //Levek::printMat4(state->model);
    state->model = glm::scale(state->model, transform->scale);
    //Levek::printMat4(state->model);

}

void cleanMeshPipelineState(MeshPipelineState* state) {
    if (state != nullptr) {
        delete state->vb;
        delete state->ib;
        delete state->va;
    }
}

int main(void) {

    std::cout << "Launching dragon example" << std::endl; 

    Levek::RenderingEngine* engine = new Levek::RenderingEngine(1000, 800);
    Levek::WindowController* windowController = engine->getWindowController();
    Levek::InputController* inputController = engine->getInputController();
    
    ///////
    Levek::MeshPipelineState meshPipelineState(
        engine->getModelLoader(),
        LEVEKGL_RESOURCES_DIRECTORY"/models/voxel_cat.obj", 
        LEVEKGL_RESOURCES_DIRECTORY"/textures/voxel_cat.png"
    ); 
    
    Levek::Renderer* renderer = engine->getRenderer();
    Levek::LineRenderer* lineRenderer = engine->getLineRenderer();

    renderer->setClearColor({0.40f, 0.40f, 0.0f, 0.0f});
    
    Levek::PerspectiveCamera camera({0, 0, 1}, {0, 0, -1}, {0, 1, 0}, 1000, 800);

    Levek::Shader shader = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/simple_mesh/shaders/phong.vert",
        SAMPLES_DIRECTORY"/simple_mesh/shaders/phong.frag"
    );

    Levek::SkyBoxPipelineState skyboxState;

    glm::vec3 lightDirection = glm::vec3(0.1, -1, 0.1);
    glm::vec3 lightDirectionView;
    glm::mat4 projection = camera.getProjection();

    //or {0, 0, 0}, {0, 1, 0}, {0, 0, 1}
    Levek::OrthographicCamera lightCamera({0, 0, 0}, {0, -1, 0}, {0, 0, 1}, -50.0f, 50.0f, -50.0f, 50.0f, -100.0f, 100.0f);

    Levek::FrameBuffer depthMap (2048, 2048);
    Levek::Texture depthTexture(2048, 2048, Levek::TextureParameters::TextureType::DEPTH);

    depthMap.addDepthAttachment(depthTexture);
    depthMap.finalize();
    depthMap.unbind();

    Levek::Shader depthShader = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/simple_mesh/shaders/shadow.vert",
        SAMPLES_DIRECTORY"/simple_mesh/shaders/shadow.frag"
    );

    while (!windowController->exit()) {

        //std::cout << windowController->getDeltaTime() << std::endl;
        renderer->clear();
        renderer->clear(depthMap);
        
        UpdateCameraPositionWASD(inputController, camera, windowController->getDeltaTime(), 0.00001f);
    
        //UpdateCameraPositionWASD(inputController, lightCamera, windowController->getDeltaTime(), 10.0f);
        lightCamera.setEye(camera.getEye());
        UpdateCameraWithMouseOnDrag(inputController, camera, 0.2f);
        lineRenderer->SetViewProjection(camera.getProjection() * camera.getView());
        
        UpdateCameraPositionWASD(inputController, camera, windowController->getDeltaTime(), 40.0f);
        UpdateCameraWithMouseOnDrag(inputController, camera, 0.1f);

        //render the shadow here

        glm::mat4& view = camera.getView();
        glm::mat3& normalView = camera.getNormalView();

        lightDirectionView = glm::normalize(normalView * lightDirection);

        /*
        glm::mat4 model(1.0f);
		model = glm::translate(model, transform->position);
        model *= glm::mat4_cast(transform->rotation);
        model = glm::scale(model, transform->scale);
        */

        glm::mat4 vp = camera.getProjection() * glm::mat4(glm::mat3(camera.getView()));
        skyboxState.draw(renderer, vp);

        lineRenderer->AddLine({0, 0, 0}, {1, 0, 0}, {1.0, 0, 0, 1.0});
        lineRenderer->AddLine({0, 0, 0}, {0, 1, 0}, {0.0, 1.0, 0, 1.0});
        lineRenderer->AddLine({0, 0, 0}, {0, 0, 1}, {0, 0, 1.0, 1.0});
        lineRenderer->Draw();

        inputController->poll();
        windowController->swapBuffers();
    }


    delete engine;
    return 0;
}