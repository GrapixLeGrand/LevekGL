
project(hello_triangle)

add_executable(hello_triangle hello_triangle.cpp)

target_link_libraries(hello_triangle LevekGL)

#target_include_directories(hello_triangle ${LEVEKGL_TARGET_INCLUDE_DIRS})
#add_custom_command(TARGET hello_triangle POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_FILE:assimp> $<TARGET_FILE_DIR:hello_triangle>
#        )

