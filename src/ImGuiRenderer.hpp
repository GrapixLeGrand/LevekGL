
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#define IMGUI_OPENGL3_GLSL_VERSION "#version 130"

#ifndef LEVEK_IMGUI_RENDERER
#define LEVEK_IMGUI_RENDERER

class ImGuiRenderer {

private:

public:

    void Initialize(GLFWwindow* window) {
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init(IMGUI_OPENGL3_GLSL_VERSION);
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();
    }

    void Destroy() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void BeginRecordFrame() {
        ImGui::Begin("Test");
    }

    void EndRecordFrame() {
        ImGui::End();
    }

    void BeginFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void EndFrame() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

};

#endif