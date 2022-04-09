cmake_minimum_required(VERSION 3.13)
cmake_policy(SET CMP0079 NEW)
project(LevekGL VERSION 0.1.0)

message("LevekGL: build type is ${CMAKE_BUILD_TYPE}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("LevekGL: building in debug mode")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("LevekGL: building in release mode")
else()
    message(FATAL_ERROR "LevekGL: building in other mode")
endif()

#need to do this otherwise the CMake cache could hount us down
#unset(LEVEKGL_USE_INTERNAL_GLM CACHE)
#unset(LEVEKGL_BUILD_SAMPLES CACHE)



OPTION(LEVEKGL_BUILD_SAMPLES
  "Build samples with the library."
  ON
)

OPTION(LEVEKGL_USE_INTERNAL_GLM
  "ON/OFF and if ON nothing is required. If OFF, must specify ENV{LEVEKGL_USE_INTERNAL_GLM}"
  ON
)

message("LevekGL: use internal GLM state: $ENV{LEVEKGL_USE_INTERNAL_GLM}")

add_compile_definitions(RESOURCES_DIRECTORY="${LevekGL_SOURCE_DIR}/src/resources")

set(OpenGL_GL_PREFERENCE "GLVND") #between GLVND and LEGACY

#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

find_package(OpenGL REQUIRED)

add_subdirectory(thirdparty)
add_subdirectory(src)

if (UNIX)
    message("Levek: Compiling for Unix")
    find_package(GLUT REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glfw3 REQUIRED)
endif (UNIX)


link_directories(${LevekGL_SOURCE_DIR}/src)

set(LEVEKGL_SOURCES

    "src/OpenGLError.cpp"

    "src/buffer/FrameBuffer.cpp"
    "src/buffer/IndexBuffer.cpp"
    "src/buffer/VertexBuffer.cpp"
    "src/buffer/VertexArray.cpp"
    
    "src/layout/BufferLayout.cpp"
    "src/layout/VertexBufferLayout.cpp"
    
    #"src/layout/VertexBufferLayoutInstancing.cpp"

    "src/renderer/Renderer.cpp"
    "src/renderer/PointRenderer.cpp"
    "src/renderer/LineRenderer.cpp"

    "src/mesh/Primitives.cpp"

    "src/shader/GlslangCompiler.cpp"
    "src/shader/Shader.cpp"
    "src/shader/ShaderFactory.cpp"
    "src/shader/ShaderManager.cpp"

    "src/texture/Texture.cpp"
    "src/texture/CubeMap.cpp"
    "src/texture/RenderBuffer.cpp"
    "src/texture/TextureProperties.cpp"

    "src/input/GLFWInputController.cpp"
    "src/window/GLFWWindowController.cpp"

    "src/mesh/loader/AssimpModelLoader.cpp"

    "src/RenderingEngine.cpp"

    "src/scene/Camera.cpp"
    "src/scene/PerspectiveCamera.cpp"
    "src/scene/OrthographicCamera.cpp"

    "src/utils/Utils.cpp"
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

if (UNIX)
    set(ASSIMP_INCLUDE_DIR "thirdparty/assimp-5.1.4")
elseif(WIN32)
    set(ASSIMP_INCLUDE_DIR "thirdparty/windows/assimp/assimp-5.2.3/include")
endif()
message("LevekGL: assimp include dir: ${ASSIMP_INCLUDE_DIR}")

set(GLM_INCLUDE_DIR "thirdparty/glm-0.9.9.8")

if (NOT LEVEKGL_USE_INTERNAL_GLM)
    message("LevekGL: setting external glm path to $ENV{LEVEKGL_EXTERNAL_GLM_PATH}")
    set(GLM_INCLUDE_DIR $ENV{LEVEKGL_EXTERNAL_GLM_PATH})
else()
    message("LevekGL: using normal glm path")
endif()

set(LEVEKGL_TARGET_INCLUDE_DIRS 
    PUBLIC "thirdparty/imgui-1.83"
    PUBLIC "thirdparty/imgui-1.83/backends"
    PUBLIC "thirdparty/stb_image-2.27"
    PUBLIC "${LevekGL_SOURCE_DIR}/src"
    PUBLIC "${GLM_INCLUDE_DIR}"
    PUBLIC "${ASSIMP_INCLUDE_DIR}"
    PUBLIC "thirdparty/glslang"
)



if (WIN32)
    set(GLEW_INCLUDE_DIRS "thirdparty/windows/glew-2.1.0/include")
    set(GLFW3_INCLUDE_DIRS "thirdparty/windows/glfw-3.3.6/include")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(GLEW_LIBRARIES "${LevekGL_SOURCE_DIR}/thirdparty/windows/glew-2.1.0/lib/MDd/glewd.lib")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(GLEW_LIBRARIES "${LevekGL_SOURCE_DIR}/thirdparty/windows/glew-2.1.0/lib/MD/glew.lib")   
    endif()
    set(GLFW3_LIBRARIES "${LevekGL_SOURCE_DIR}/thirdparty/windows/glfw-3.3.6/lib-vc2022/glfw3.lib")
endif (WIN32)

#include_directories(${LEVEKGL_TARGET_INCLUDE_DIR})
target_include_directories(LevekGL ${LEVEKGL_TARGET_INCLUDE_DIRS})

message("glew include dirs: ${GLEW_INCLUDE_DIRS}")
message("glew library: ${GLEW_LIBRARIES}")
message("glfw3 include dirs: ${GLFW3_INCLUDE_DIRS}")
message("glfw3 library: ${GLFW3_LIBRARIES}")
message("OpenGL include dirs: ${OPENGL_INCLUDE_DIR}")
message("OpenGL library: ${OPENGL_LIBRARIES}")

if (UNIX)
    message("linking opengl Unix")
    include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(LevekGL glfw)
    target_link_libraries(LevekGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}  ${GLEW_LIBRARIES})
endif (UNIX)
if (WIN32)
    message("linking opengl windows")
    include_directories(${GLFW3_INCLUDE_DIRS})
    include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
    add_library(glfw STATIC IMPORTED)
    set_property(TARGET glfw PROPERTY IMPORTED_LOCATION ${GLFW3_LIBRARIES})
    target_link_libraries(LevekGL glfw)
    add_library(glew32s STATIC IMPORTED)
    set_property(TARGET glew32s PROPERTY IMPORTED_LOCATION ${GLEW_LIBRARIES})
    target_link_libraries(LevekGL ${OPENGL_LIBRARIES} glew32s)
    target_compile_definitions(LevekGL PRIVATE GLEW_STATIC)
    add_compile_definitions(PLATFORM_WINDOWS)
endif(WIN32)

set(BUILD_SHARED_LIBS OFF)

if (UNIX)
    target_link_libraries(LevekGL assimp)
elseif(WIN32)
    message("LevekGL: using assimp for windows")
    add_library(assimp STATIC IMPORTED)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set_property(TARGET assimp PROPERTY IMPORTED_LOCATION "${LevekGL_SOURCE_DIR}/thirdparty/windows/assimp/MDd/lib/assimpd.lib")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_property(TARGET assimp PROPERTY IMPORTED_LOCATION "${LevekGL_SOURCE_DIR}/thirdparty/windows/assimp/MD/lib/assimp.lib")
    endif()
    target_link_libraries(LevekGL assimp)
endif()



#bellow linkages are for glslang
target_link_libraries(LevekGL glslang)

set(LEVEKGL_INCLUDE_DIR ${LevekGL_SOURCE_DIR})

add_compile_definitions(SAMPLES_DIRECTORY="${LevekGL_SOURCE_DIR}/samples")

if(${LEVEKGL_BUILD_SAMPLES})
    message("LevekGL: building samples")
    add_subdirectory(samples)
else()
    message("LevekGL: not building samples")
endif()