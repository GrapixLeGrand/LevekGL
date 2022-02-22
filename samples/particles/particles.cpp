#include <iostream>
#include <cstdlib>
#include <ctime>

#include "LevekGL.hpp"
#include "../Utils.hpp"

int resolutionX = 1280;
int resolutionY = 720;

int main(void) {

    Levek::RenderingEngine* engine = new Levek::RenderingEngine(resolutionX, resolutionY);

    Levek::Renderer* renderer = engine->getRenderer();
    Levek::LineRenderer* lineRenderer = engine->getLineRenderer();
    Levek::WindowController* windowController = engine->getWindowController();
    Levek::InputController* inputController = engine->getInputController();

    windowController->setWindowTitle("Particles");
    windowController->initImGui();

    Levek::ModelLoader* meshLoader = engine->getModelLoader();
    Levek::Model* model = meshLoader->loadFromFile(SAMPLES_DIRECTORY"/particles/billboard.obj");
    const Levek::Mesh* sphere = model->getMesh(0);

    Levek::PerspectiveCamera camera({3.6, 1.5, 3.6}, {0.2, 0.2, 0.2}, {0, 1, 0}, resolutionX, resolutionY);
    glm::mat4 projection = camera.getProjection();

    Levek::Shader shaderInstances = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/particles/sphere_inst.vert",
        SAMPLES_DIRECTORY"/particles/sphere_inst.frag"
    );
    
    int num_particles = 100000;
    int lim = 100; //(num_particles, {0, 0, 0});
    std::vector<glm::vec3> particlesPositions (num_particles, {0, 0, 0}); // { {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0} };
    for (int i = 0; i < num_particles; i++) {
        particlesPositions[i].x = std::rand() % lim;
        particlesPositions[i].y = std::rand() % lim;
        particlesPositions[i].z = std::rand() % lim;
    }
    
    Levek::VertexBuffer particlesPositionsVBO = Levek::VertexBuffer(particlesPositions.data(), particlesPositions.size() * 3 * 4);

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

    //plan state

    Levek::Shader planeShader = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/particles/ground.vert",
        SAMPLES_DIRECTORY"/particles/ground.frag"
    );

    Levek::Model* planeModel = meshLoader->loadFromFile(SAMPLES_DIRECTORY"/resources/plane.obj");
    const Levek::Mesh* planeMesh = planeModel->getMesh(0);
    //Levek::Mesh planeMesh = Levek::makePlane(1.0f);
    Levek::VertexBuffer planeVBO = Levek::VertexBuffer(planeMesh);
    Levek::IndexBuffer planeIBO = Levek::IndexBuffer(planeMesh);
    Levek::VertexBufferLayout planeLayout = Levek::VertexBufferLayout();
    planeLayout.push<glm::vec3>(1);
    planeLayout.push<glm::vec2>(1);
    planeLayout.push<glm::vec3>(1);
    Levek::VertexArray planeVA;
    planeVA.addBuffer(planeVBO, planeLayout);
    
    Levek::Texture unitTexture = Levek::Texture(SAMPLES_DIRECTORY"/resources/unit.png");
    unitTexture.set(Levek::TextureParameters::TextureWrapMode::REPEAT);
    unitTexture.set(Levek::TextureParameters::TextureLODFunction::LINEAR, Levek::TextureParameters::TextureLODFunction::LINEAR);
    
    //glm::mat4 planeModel = glm::mat4(1.0f);

    while (!windowController->exit() && !inputController->isKeyPressed(Levek::LEVEK_KEY_Q)) {            

        renderer->clear();

        UpdateCameraPositionWASD(inputController, camera, windowController->getDeltaTime(), 10.f);
        UpdateCameraWithMouseOnDrag(inputController, camera, 0.2f);

        glm::mat4 view = camera.getView();
        glm::mat4 vp = camera.getProjection() * camera.getView();
        glm::mat3 view_inv = glm::inverse(glm::mat3(view)); //for billboard facing: see https://stackoverflow.com/questions/61559585/how-to-remove-rotation-from-model-view-matrix-so-that-object-always-faces-camera
        glm::mat3 normalView = camera.getNormalView();
        glm::mat3 normalViewInv = glm::inverse(normalView);
        //glm::vec3(0, -1, 0); //
        glm::vec3 lightDirection = glm::vec3(0, -1, 0); //glm::vec3(glm::normalize(view * glm::vec4(0, -1, 0, 0)));
        glm::mat4 view_inv_t = glm::inverse(view);


        //render instances
        shaderInstances.bind();
        shaderInstances.setUniformMat4f("vp", vp);
        shaderInstances.setUniformMat3f("normal_view", camera.getNormalView());
        shaderInstances.setUniformMat3f("normal_view_inv", normalViewInv);
        shaderInstances.setUniformMat4f("v", camera.getView());
        shaderInstances.setUniformMat4f("view_inv_t", view_inv_t);
        shaderInstances.setUniformMat4f("p", camera.getProjection());
        shaderInstances.setUniformMat3f("view_inv", view_inv);
        shaderInstances.setUniform3f("light_direction", lightDirection);

        glm::vec4 c {1.0, 0.0, 0.5, 1.0};
        shaderInstances.setUniform4f("color", c);

        vp = camera.getProjection() * glm::mat4(glm::mat3(camera.getView()));
        skybox.draw(renderer, vp);
        renderer->drawInstances(&particlesVA, &sphereIBO, &shaderInstances, particlesPositions.size());
        
        //render plane
        planeShader.bind();
        unitTexture.activateAndBind(0);
        vp = camera.getProjection() * camera.getView();
        planeShader.setUniformMat4f("mvp", vp);
        planeShader.setUniform1i("tex", 0);
        renderer->draw(&planeVA, &planeIBO, &planeShader);

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