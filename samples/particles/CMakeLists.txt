project(particles)

add_executable(particles particles.cpp simulation.cpp ../Utils.cpp)

target_link_libraries(particles LevekGL)