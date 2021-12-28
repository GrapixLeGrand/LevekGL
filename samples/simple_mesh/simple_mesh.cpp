#include <iostream>

#include "LevekGL.hpp"
#include "../Utils.hpp"
#include "glm/gtc/quaternion.hpp"

int main(void) {

    std::cout << "Launching dragon example" << std::endl; 

    Levek::RenderingEngine* engine = new Levek::RenderingEngine(800, 600);
    Levek::WindowController* windowController = engine->getWindowController();
    Levek::InputController* inputController = engine->getInputController();
    
    Levek::ModelLoader* meshLoader = engine->getModelLoader();
    Levek::Model* model = meshLoader->loadFromFile(SAMPLES_DIRECTORY"/simple_mesh/dragon.obj");

    Levek::Renderer* renderer = engine->getRenderer();
    Levek::LineRenderer* lineRenderer = engine->getLineRenderer();

    renderer->setClearColor({0.40f, 0.40f, 0.0f, 0.0f});
    
    Levek::PerspectiveCamera camera({0, 0, 1}, {0, 0, -1}, {0, 1, 0}, 800, 600);

    
    Levek::Mesh* mesh = model->getMesh(0);
    Levek::Transform* transform = model->getTransform(0);

    int n = mesh->getVertices().size();

    Levek::VertexArray vertexArray;
    Levek::VertexBuffer vertexBuffer(mesh);
    Levek::IndexBuffer indexBuffer(mesh);

    Levek::VertexBufferLayout layout = Levek::VertexBufferLayout();
    layout.push<glm::vec3>(1);
    layout.push<glm::vec2>(1);
    layout.push<glm::vec3>(1);

    vertexArray.addBuffer(vertexBuffer, layout);

    vertexBuffer.unbind();
    indexBuffer.unbind();
    vertexArray.unbind();

    Levek::Shader shader = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/simple_mesh/phong.vert",
        SAMPLES_DIRECTORY"/simple_mesh/phong.frag"
    );

    //Levek::PerspectiveCamera camera({1, 1, 1}, {0, 0, 0}, {0, 1, 0}, 800, 600);
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
    
    Levek::printMat4(lightCamera.getProjection());
    Levek::printMat4(lightCamera.getView());

    while (!windowController->exit()) {

        renderer->clear();
        renderer->clear(depthMap);
        
        UpdateCameraPositionWASD(inputController, camera, windowController->getDeltaTime(), 10.0f);
        UpdateCameraPositionWASD(inputController, lightCamera, windowController->getDeltaTime(), 10.0f);
        //UpdateCameraPositionWASD(inputController, lightCamera, windowController->getDeltaTime(), 10.0f);
        UpdateCameraWithMouseOnDrag(inputController, camera, 0.5f);
        lineRenderer->SetViewProjection(camera.getProjection() * camera.getView());
        
        
        UpdateCameraPositionWASD(inputController, camera, windowController->getDeltaTime(), 40.0f);
        UpdateCameraWithMouseOnDrag(inputController, camera, 0.1f);

        //render the shadow here

        glm::mat4& view = camera.getView();
        glm::mat3& normalView = camera.getNormalView();

        lightDirectionView = glm::normalize(normalView * lightDirection);

        glm::mat4 model(1.0f);
		model = glm::translate(model, transform->position);
        model *= glm::mat4_cast(transform->rotation);
        model = glm::scale(model, transform->scale);

        glm::mat4 lightMVP = lightCamera.getProjection() * lightCamera.getView() * model;

        depthShader.bind();
        depthShader.setUniformMat4f("light_mvp", lightMVP);
        depthShader.unbind();

        renderer->draw(&depthMap, &vertexArray, &indexBuffer, &depthShader);
        renderer->draw(depthTexture);
        
        //render the object here 

        glm::mat4 modelView = camera.getView() * model;
        glm::mat3 normal = camera.getNormalView() * glm::mat3(model);
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

        renderer->draw(&vertexArray, &indexBuffer, &shader);
        
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