cmake_minimum_required(VERSION 3.0.0)
project(LevekGL VERSION 0.1.0)

add_compile_definitions(RESOURCES_DIRECTORY="${LevekGL_SOURCE_DIR}/src/resources")

set(OpenGL_GL_PREFERENCE "GLVND") #between GLVND and LEGACY

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(thirdparty)
add_subdirectory(src)

link_directories(${LevekGL_SOURCE_DIR}/src)

set(LEVEKGL_SOURCES
    "src/OpenGLError.cpp"

    "src/buffer/FrameBuffer.cpp"
    "src/buffer/IndexBuffer.cpp"
    "src/buffer/VertexBuffer.cpp"
    "src/buffer/VertexArray.cpp"
    
    "src/layout/VertexBufferLayout.cpp"
    "src/layout/VertexBufferLayoutInstancing.cpp"

    "src/renderer/Renderer.cpp"

    "src/shader/Shader.cpp"
    "src/shader/ShaderFactory.cpp"
    "src/shader/ShaderManager.cpp"

    "src/texture/Texture.cpp"
    "src/texture/RenderBuffer.cpp"
    "src/texture/TextureProperties.cpp"

    "src/input/GLFWInputController.cpp"
    "src/window/GLFWWindowController.cpp"

    "src/RenderingEngine.cpp"

)

set(IMGUI_SRC 
    "thirdparty/imgui-1.83/imgui.h"
    "thirdparty/imgui-1.83/imgui_widgets.cpp"
    "thirdparty/imgui-1.83/imgui.cpp"
    "thirdparty/imgui-1.83/imgui_tables.cpp"
    "thirdparty/imgui-1.83/imgui_demo.cpp"
    "thirdparty/imgui-1.83/imgui_draw.cpp"
    "thirdparty/imgui-1.83/backends/imgui_impl_opengl3.cpp"
    "thirdparty/imgui-1.83/backends/imgui_impl_glfw.cpp"
)

set(STB_IMAGE_SRC 
    "thirdparty/stb_image-2.27/stb_image.cpp"
)

set(LEVEKGL_ALL_SOURCES ${IMGUI_SRC} ${STB_IMAGE_SRC} ${LEVEKGL_SOURCES})

#compile the project as a library
add_library(LevekGL STATIC ${IMGUI_SRC} ${STB_IMAGE_SRC} ${LEVEKGL_SOURCES})
target_compile_features(LevekGL PRIVATE cxx_std_17)

set(LEVEKGL_TARGET_INCLUDE_DIRS 
    PUBLIC "thirdparty/imgui-1.83"
    PUBLIC "thirdparty/imgui-1.83/backends"
    PUBLIC "thirdparty/stb_image-2.27"
    PUBLIC "${LevekGL_SOURCE_DIR}/src"
    #PUBLIC ""
)

target_include_directories(LevekGL ${LEVEKGL_TARGET_INCLUDE_DIRS})

#include(LevekGL "LevekGL.hpp")
#target_include_directories(LevekGL PRIVATE src)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

target_link_libraries(LevekGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}  ${GLEW_LIBRARIES})
target_link_libraries(LevekGL glfw)

set(LEVEKGL_INCLUDE_DIR ${LevekGL_SOURCE_DIR})

add_compile_definitions(SAMPLES_DIRECTORY="${LevekGL_SOURCE_DIR}/samples")
add_subdirectory(samples)