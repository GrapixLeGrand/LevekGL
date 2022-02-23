#pragma once

#include <vector>
#include "glm/glm.hpp"

struct Simulation {

    float particleDiameter = 1.0;
    float particleRadius = 0.5;
    float kernelRadius = 3.1 * particleDiameter;

    int max_neighbors;

    int particlesX;
    int particlesY;
    int particlesZ;
    int num_particles;

    float domainX = 10.0f;
    float domainY = 10.0f;
    float domainZ = 10.0f;

    float rest_density = 1000.0;
    float mass = 1.0;

    glm::vec3 gravity = glm::vec3(0, -10.0, 0.0);
    float time_step = 0.01;
    float steps = 4;

    float relaxation_epsilon = 1.0;

    float dt_s_corr = 0.041;
    float k_s_corr = 0.110;
    float n_scorr = 4;

    float c_xsph = 0.1;
    float epsilon_vorticity = 0.1;
    
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> positions_star;
    std::vector<glm::vec3> velocities;
    std::vector<glm::vec3> pressures_forces;

    std::vector<float> densities;
    std::vector<float> lambdas;

    std::vector<glm::vec3> vorticities;

    std::vector<std::vector<int>> neighbors;

    std::vector<glm::vec4> colors;

    //stuff for the kernel
    float cubic_kernel_k;
    float cubic_kernel_l;

};

extern void init_sim(Simulation* simulation, int particlesX, int particlesY, int particlesZ);
extern void fill_grid(Simulation* simulation);
extern void find_neighbors(Simulation* simulation);
extern void clear_neighbors(Simulation* simulation);

/**
 * @brief cubic kernel. from SplishSplash repository https://github.com/InteractiveComputerGraphics/SPlisHSPlasH/blob/master/SPlisHSPlasH/SPHKernels.h 
 * 
 * @param simulation 
 * @param r 
 * @return float 
 */
extern float cubic_kernel(const Simulation* simulation, float r);


/**
 * @brief cubic kernel. from SplishSplash repository https://github.com/InteractiveComputerGraphics/SPlisHSPlasH/blob/master/SPlisHSPlasH/SPHKernels.h 
 * 
 * @param simulation 
 * @param r 
 * @return float 
 */
extern float cubic_kernel(const Simulation* simulation, glm::vec3& r);

/**
 * @brief gradient of cubic kernel. from SplishSplash repository https://github.com/InteractiveComputerGraphics/SPlisHSPlasH/blob/master/SPlisHSPlasH/SPHKernels.h 
 * 
 * @param simulation 
 * @param r 
 * @return float 
 */
extern glm::vec3 cubic_kernel_grad(const Simulation* simulation, const glm::vec3& r);

extern void simulate(Simulation* simulation);