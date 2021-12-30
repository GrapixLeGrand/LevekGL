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

    Levek::printMat4(state->model);
    state->model = glm::translate(state->model, transform->position);
    Levek::printMat4(state->model);
    state->model *= glm::mat4_cast(transform->rotation);
    Levek::printMat4(state->model);
    state->model = glm::scale(state->model, transform->scale);
    Levek::printMat4(state->model);

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
    
    Levek::ModelLoader* meshLoader = engine->getModelLoader();
    Levek::Model* model = meshLoader->loadFromFile(SAMPLES_DIRECTORY"/simple_mesh/cats.dae");

    std::vector<MeshPipelineState> pipelineStates (model->getNumMeshes());

    for (size_t i = 0; i < pipelineStates.size(); i++) {
        initMeshPipelineState(&pipelineStates[i], model->getMesh(i), model->getTransform(i));
    }

    Levek::Renderer* renderer = engine->getRenderer();
    Levek::LineRenderer* lineRenderer = engine->getLineRenderer();

    renderer->setClearColor({0.40f, 0.40f, 0.0f, 0.0f});
    
    Levek::PerspectiveCamera camera({0, 0, 1}, {0, 0, -1}, {0, 1, 0}, 1000, 800);

    Levek::Shader shader = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/simple_mesh/phong.vert",
        SAMPLES_DIRECTORY"/simple_mesh/phong.frag"
    );

    //Levek::PerspectiveCamera camera({1, 1, 1}, {0, 0, 0}, {0, 1, 0}, 1000, 800);
    glm::vec3 lightDirection = glm::vec3(0.1, -1, 0.1);
    glm::vec3 lightDirectionView;
    glm::mat4 projection = camera.getProjection();

    //or {0, 0, 0}, {0, 1, 0}, {0, 0, 1}
    Levek::OrthographicCamera lightCamera({0, 0, 0}, {0, -1, 0}, {0, 0, 1}, -10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);

    Levek::FrameBuffer depthMap (1024, 1024);
    Levek::Texture depthTexture(1024, 1024, DEPTH_24);

    depthMap.addDepthAttachment(depthTexture);
    depthMap.finalize();
    depthMap.unbind();

    Levek::Shader depthShader = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/simple_mesh/shadow.vert",
        SAMPLES_DIRECTORY"/simple_mesh/shadow.frag"
    );

    while (!windowController->exit()) {

        renderer->clear();
        renderer->clear(depthMap);
        
        UpdateCameraPositionWASD(inputController, camera, windowController->getDeltaTime(), 10.0f);
        //UpdateCameraPositionWASD(inputController, lightCamera, windowController->getDeltaTime(), 10.0f);
        lightCamera.setEye(camera.getEye());
        UpdateCameraWithMouseOnDrag(inputController, camera, 0.5f);
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

        for (size_t i = 0; i < pipelineStates.size(); i++) {

            auto& currentState = pipelineStates[i];

            glm::mat4 lightMVP = lightCamera.getProjection() * lightCamera.getView() * currentState.model;

            depthShader.bind();
            depthShader.setUniformMat4f("light_mvp", lightMVP);
            depthShader.unbind();

            renderer->draw(&depthMap, currentState.va, currentState.ib, &depthShader);
            renderer->draw(depthTexture, {0.75f, 0.75f}, {0.25f, 0.25f});
            
            //render the object here 

            glm::mat4 modelView = camera.getView() * currentState.model;
            glm::mat3 normal = camera.getNormalView() * glm::mat3(currentState.model);
            glm::mat4 mvp = camera.getProjection() * modelView;

            shader.bind();
            shader.setUniformMat4f("light_mvp", lightMVP);
            depthTexture.activateAndBind(0);
            shader.setUniform1i("shadowMap", 0);
            shader.setUniformMat4f("mvp", mvp);
            shader.setUniformMat4f("mv", modelView);
            shader.setUniformMat3f("normalMatrix", normal);
            shader.setUniform3f("lightDirectionView", lightDirectionView);
            shader.unbind();

            renderer->draw(currentState.va, currentState.ib, &shader);
        }

        lineRenderer->AddLine({0, 0, 0}, {1, 0, 0}, {1.0, 0, 0, 1.0});
        lineRenderer->AddLine({0, 0, 0}, {0, 1, 0}, {0.0, 1.0, 0, 1.0});
        lineRenderer->AddLine({0, 0, 0}, {0, 0, 1}, {0, 0, 1.0, 1.0});

        lineRenderer->Draw();

        inputController->poll();
        windowController->swapBuffers();
    }

    for (size_t i = 0; i < pipelineStates.size(); i++) {
        cleanMeshPipelineState(&pipelineStates[i]);
    }

    delete engine;
    return 0;
}