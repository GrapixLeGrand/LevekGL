#include <iostream>
#include <cstdlib>
#include <ctime>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "LevekGL.hpp"
#include "../Utils.hpp"
#include "simulation.hpp"

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
    Levek::Model* model = meshLoader->loadFromFile(SAMPLES_DIRECTORY"/particles/models/billboard.obj");
    const Levek::Mesh* sphere = model->getMesh(0);

    Levek::PerspectiveCamera camera({20, 20, 45}, {0.2, 0.2, 0.2}, {0, 1, 0}, resolutionX, resolutionY);
    glm::mat4 projection = camera.getProjection();

    Levek::Shader shaderInstances = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/particles/shaders/sphere_inst.vert",
        SAMPLES_DIRECTORY"/particles/shaders/sphere_inst.frag"
    );
    
    float particleScale = 1.0f;

    Simulation simulation;
    int particleX = 20;
    int particleY = 30;
    int particleZ = 20;
    init_sim(&simulation, particleX, particleY, particleZ);
    fill_grid(&simulation);

    /*
    int num_particles = 1000;
    int lim = 10; //(num_particles, {0, 0, 0});
    int num_colors = 256;
    std::vector<glm::vec3> particlesPositions (num_particles, {0, 0, 0}); // { {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0} };
    std::vector<unsigned int> particlesColors (num_particles, 0);
    std::vector<glm::vec4> palette (num_colors, {0, 0, 0, 1.0});
    for (int i = 0; i < num_particles; i++) {
        particlesPositions[i].x = std::rand() % lim;
        particlesPositions[i].y = std::rand() % lim;
        particlesPositions[i].z = std::rand() % lim;
        particlesColors[i] = std::rand() % 16;
        if (i < num_colors)  {
            palette[i].r = ((float) std::rand() / RAND_MAX);
            palette[i].g = ((float) std::rand() / RAND_MAX);
            palette[i].b = ((float) std::rand() / RAND_MAX);
            palette[i].a = 1.0f;
        }
    }*/

    Levek::VertexBuffer particlesPositionsVBO = Levek::VertexBuffer(simulation.positions.data(), simulation.positions.size() * 3 * 4);
    Levek::VertexBuffer particlesColorsVBO = Levek::VertexBuffer(simulation.colors.data(), simulation.colors.size() * 4 * 4);

    Levek::VertexBuffer sphereVBO = Levek::VertexBuffer(sphere);
    Levek::IndexBuffer sphereIBO = Levek::IndexBuffer(sphere);
    Levek::VertexBufferLayout sphereLayout = Levek::VertexBufferLayout();
    Levek::VertexBufferLayout instanceLayout = Levek::VertexBufferLayout(); 
    Levek::VertexBufferLayout colorLayout = Levek::VertexBufferLayout();
    sphereLayout.push<glm::vec3>(1); //sphere position
    sphereLayout.push<glm::vec2>(1); //sphere textures
    sphereLayout.push<glm::vec3>(1); //sphere normal 
    instanceLayout.push<glm::vec3>(1, 1); //instance offset (per instance)
    colorLayout.push<glm::vec4>(1, 1);

    Levek::VertexArray particlesVA;
    particlesVA.addBuffer(sphereVBO, sphereLayout);
    particlesVA.addBuffer(particlesPositionsVBO, instanceLayout);
    particlesVA.addBuffer(particlesColorsVBO, colorLayout);

    SkyBoxPipelineState skybox (getSkyBoxPaths());

    //plan state

    Levek::Shader planeShader = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/particles/shaders/ground.vert",
        SAMPLES_DIRECTORY"/particles/shaders/ground.frag"
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
    float factor = 1.0f;

    while (!windowController->exit() && !inputController->isKeyPressed(Levek::LEVEK_KEY_Q)) {            

        //simulation.time_step = windowController->getDeltaTime();
        //sim here
        simulate(&simulation);

        particlesPositionsVBO.Update(simulation.positions.data(), simulation.positions.size() * 3 * 4);
        renderer->clear();

        UpdateCameraPositionWASD(inputController, camera, windowController->getDeltaTime(), 10.f);
        UpdateCameraWithMouseOnDrag(inputController, camera, 0.2f);

        glm::mat4 view = camera.getView();
        glm::mat4 vp = camera.getProjection() * camera.getView();
        glm::mat3 view_inv = glm::inverse(glm::mat3(view)); //for billboard facing: see https://stackoverflow.com/questions/61559585/how-to-remove-rotation-from-model-view-matrix-so-that-object-always-faces-camera
        glm::vec3 lightDirection = glm::vec3(0, -1, 0); //glm::vec3(glm::normalize(view * glm::vec4(0, -1, 0, 0)));

        //render instances
        shaderInstances.bind();
        shaderInstances.setUniformMat4f("vp", vp);
        shaderInstances.setUniformMat4f("p", camera.getProjection());
        shaderInstances.setUniformMat4f("view", camera.getView());
        shaderInstances.setUniformMat3f("view_inv", view_inv);
        shaderInstances.setUniform3f("light_direction", lightDirection);
        //shaderInstances.setUniform4f("palette", palette.data(), 256);
        shaderInstances.setUniform1f("scale", particleScale);

        vp = camera.getProjection() * glm::mat4(glm::mat3(camera.getView()));
        skybox.draw(renderer, vp);
        renderer->drawInstances(&particlesVA, &sphereIBO, &shaderInstances, simulation.num_particles);
        
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
        ImGuiTabBarFlags flags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable;
        ImGui::Begin("Scene");
        ImGui::BeginTabBar("Scene parameters");
        if (ImGui::BeginTabItem("Simulation")) {

            ImGui::Text("%d fps", (int) (1.0f / windowController->getDeltaTime()));
            ImGui::Text("particle radius %.3f", simulation.particleRadius);
            ImGui::Text("particle diameter %.3f", simulation.particleDiameter);
            ImGui::Text("kernel radius %.3f", simulation.kernelRadius);
            ImGui::Text("#particles: %d", simulation.num_particles);

            //ImGui::InputFloat("kernel factor", &factor, 0.001f, 100.0f, "%.3f");
            ImGui::InputFloat("cubic k", &simulation.cubic_kernel_k, 0.01f, 100.0f, "%.3f");
            ImGui::InputFloat("cubic l", &simulation.cubic_kernel_l, 0.01f, 100.0f, "%.3f");
            ImGui::InputFloat("rest density", &simulation.rest_density, 0.01f, 3000.0f, "%.3f");
            ImGui::InputFloat("mass", &simulation.mass, 0.01f, 1000.0f, "%.3f");
            ImGui::InputFloat("relaxation", &simulation.relaxation_epsilon, 0.01f, 1000.0f, "%.3f");
            ImGui::InputFloat("kernel radius", &simulation.kernelRadius, 0.01f, 1000.0f, "%.3f");
            ImGui::InputFloat("Kernel Factor", &simulation.kernelFactor, 0.001f, 1000.0f, "%.1f");
            ImGui::SliderFloat("Kernel factor", &simulation.kernelFactor, 0.001f, 1.0f, "%.3f");

            ImGui::Text("Negative pressure correction");
            ImGui::InputFloat("s_corr dq", &simulation.s_corr_dq, 0.001f, 100.0f, "%.1f");
            ImGui::InputFloat("s_corr k", &simulation.s_corr_k, 0.001f, 100.0f, "%.1f");
            ImGui::InputFloat("s_corr n", &simulation.s_corr_n, 0.001f, 100.0f, "%.1f");

            ImGui::Text("Grid");
            //float old_cell_size = simulation.cell_size;
            //ImGui::InputFloat("cell size", &simulation.cell_size, 0.001f, 100.0f, "%.1f");

            ImGui::Text("# grid cells: %d", simulation.num_grid_cells);



            if (ImGui::Button("reset")) {
                init_sim(&simulation, particleX, particleY, particleZ);
                fill_grid(&simulation);
            }
            ImGui::EndTabItem();
            simulation.cubic_kernel_k *= factor;
            simulation.cubic_kernel_l *= factor;
        }
        if (ImGui::BeginTabItem("Particles")) {
            ImGui::InputFloat("particle size", &particleScale, 0.01f, 5.0f, "%.3f");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Camera")) {
            addImGuiVec3(camera.getEye());
            addImGuiVec3(camera.getFront());
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        lineRenderer->SetViewProjection(projection * camera.getView());
        //lineRenderer->AddLine({0, 0, 0}, {1, 0, 0}, {1.0, 0.0, 0.0, 1.0}); 
        //lineRenderer->AddLine({0, 0, 0}, {0, 1, 0}, {0.0, 1.0, 0.0, 1.0});
        //lineRenderer->AddLine({0, 0, 0}, {0, 0, 1}, {0.0, 0.0, 1.0, 1.0});

        //lineRenderer->Draw();

        inputController->poll();
        windowController->swapBuffers();
    }

    delete engine;

    return 0;
}