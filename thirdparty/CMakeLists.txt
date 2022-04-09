
 message("LevekGL::thirdparty: use of internal GLM is $ENV{LEVEKGL_USE_INTERNAL_GLM}")

if (${LEVEKGL_USE_INTERNAL_GLM})
    message("LevekGL: Using internal glm library")
    add_subdirectory(glm-0.9.9.8)
else ()
    message("LevekGL: NOT using internal glm library, using external specified at $ENV{LEVEKGL_EXTERNAL_GLM}")
    if ("$ENV{LEVEKGL_EXTERNAL_GLM_PATH}" STREQUAL "")
        message(FATAL_ERROR "LevekGL: WARNING! Using external GLM library but path is empty.")
    endif()
endif()

if (UNIX)
    add_subdirectory(assimp-5.1.4)
endif()

#if (UNIX)
#add_subdirectory(assimp-5.1.4)
#endif()

add_subdirectory(glslang)
#add_subdirectory(imgui-1.83)
