
project(assimp_test)

add_executable(assimp_test main.cpp)

target_link_libraries(assimp_test LevekGL)

#target_include_directories(hello_triangle ${LEVEKGL_TARGET_INCLUDE_DIRS})
#add_custom_command(TARGET hello_triangle POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_FILE:assimp> $<TARGET_FILE_DIR:hello_triangle>
#        )

