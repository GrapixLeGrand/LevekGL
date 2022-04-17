project(voxel_sample)

add_executable(voxel_sample main.cpp ../Utils.cpp)

target_link_libraries(voxel_sample LevekGL)