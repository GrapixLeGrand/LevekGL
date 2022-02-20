#include <iostream>
#include "LevekGL.hpp"
#include "../Utils.hpp"

int main(void) {

    Levek::RenderingEngine* engine = new Levek::RenderingEngine(1000, 800);

    Levek::Renderer* renderer = engine->getRenderer();
    Levek::LineRenderer* lineRenderer = engine->getLineRenderer();
    Levek::WindowController* windowController = engine->getWindowController();
    Levek::InputController* inputController = engine->getInputController();

    windowController->setWindowTitle("Particles");
    windowController->initImGui();

    Levek::ModelLoader* meshLoader = engine->getModelLoader();
    Levek::Model* model = meshLoader->loadFromFile(SAMPLES_DIRECTORY"/particles/sphere.obj");
    const Levek::Mesh* sphere = model->getMesh(0);

    Levek::PerspectiveCamera camera({0, 0, 1}, {0, 0, 1}, {0, 1, 0}, 1000, 800);
    glm::mat4 projection = camera.getProjection();

    

    Levek::Shader shaderInstances = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/particles/sphere_inst.vert",
        SAMPLES_DIRECTORY"/particles/sphere_inst.frag"
    );
    
    std::vector<glm::vec3> particlesPositions { {2, 0, 2}, {0, 0, 0}, {4, 0, -1} };
    Levek::VertexBuffer particlesPositionsVBO = Levek::VertexBuffer(sphere);

    Levek::VertexBuffer sphereVBO = Levek::VertexBuffer(sphere);
    Levek::IndexBuffer sphereIBO = Levek::IndexBuffer(sphere);
    Levek::VertexBufferLayout sphereLayout = Levek::VertexBufferLayout();
    Levek::VertexBufferLayout instanceLayout = Levek::VertexBufferLayout(); 
    sphereLayout.push<glm::vec3>(1); //sphere position
    sphereLayout.push<glm::vec2>(1); //sphere textures
    sphereLayout.push<glm::vec3>(1); //sphere normal 
    instanceLayout.push<glm::vec3>(1, 1); //instance offset (per instance)

    Levek::VertexArray particlesVA;
    particlesVA.addBuffer(sphereVBO, sphereLayout);
    particlesVA.addBuffer(particlesPositionsVBO, instanceLayout);

    SkyBoxPipelineState skybox (getSkyBoxPaths());

    while (!windowController->exit() && !inputController->isKeyPressed(Levek::LEVEK_KEY_Q)) {            

        renderer->clear();

        UpdateCameraPositionWASD(inputController, camera, windowController->getDeltaTime(), 1.f);
        UpdateCameraWithMouseOnDrag(inputController, camera, 0.2f);

        glm::mat4 vp = camera.getProjection() * camera.getView();

        shaderInstances.bind();
        shaderInstances.setUniformMat4f("vp", vp);
        glm::vec4 c {1.0, 0.0, 0.5, 1.0};
        shaderInstances.setUniform4f("color", c);
        
        //Levek::printVec3(camera.getFront());
        //std::cout << camera.getYaw() << " " << camera.getPitch() << " " << camera.getRoll() << std::endl;

        vp = camera.getProjection() * glm::mat4(glm::mat3(camera.getView()));
        skybox.draw(renderer, vp);
        renderer->drawInstances(&particlesVA, &sphereIBO, &shaderInstances, particlesPositions.size());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Stats");
        ImGui::Text("%d fps", (int) (1.0f / windowController->getDeltaTime()));
        ImGui::End();

        ImGui::Begin("Camera");
        addImGuiVec3(camera.getEye());
        addImGuiVec3(camera.getFront());
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        lineRenderer->SetViewProjection(projection * camera.getView());
        lineRenderer->AddLine({0, 0, 0}, {1, 0, 0}, {1.0, 0.0, 0.0, 1.0}); 
        lineRenderer->AddLine({0, 0, 0}, {0, 1, 0}, {0.0, 1.0, 0.0, 1.0});
        lineRenderer->AddLine({0, 0, 0}, {0, 0, 1}, {0.0, 0.0, 1.0, 1.0});

        lineRenderer->Draw();

        inputController->poll();
        windowController->swapBuffers();
    }

    delete engine;

    return 0;
}