cmake_minimum_required(VERSION 3.0.0)
project(LevekGL VERSION 0.1.0)

set(OpenGL_GL_PREFERENCE "GLVND") #between GLVND and LEGACY
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(thirdparty)
add_subdirectory(src)

set(IMGUI_SRC 
    "thirdparty/imgui/imgui.h"
    "thirdparty/imgui/imgui_widgets.cpp"
    "thirdparty/imgui/imgui.cpp"
    "thirdparty/imgui/imgui_tables.cpp"
    "thirdparty/imgui/imgui_demo.cpp"
    "thirdparty/imgui/imgui_draw.cpp"
    "thirdparty/imgui/backends/imgui_impl_opengl3.cpp"
    "thirdparty/imgui/backends/imgui_impl_glfw.cpp"
)

set(STB_IMAGE_SRC 
    "thirdparty/stb_image/stb_image.cpp"
)