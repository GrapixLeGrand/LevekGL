#pragma once

#include <vector>
#include "glm/glm.hpp"

struct Simulation;


typedef float (*W_fun)(const Simulation*, float);
typedef glm::vec3 (*gradW_fun)(const Simulation*, const glm::vec3&);

struct Simulation {
    
    W_fun W = nullptr;
    gradW_fun gradW = nullptr;

    float particleRadius = 0.5;
    float particleDiameter = 2 * particleRadius;
    float kernelRadius = 3.1f * particleRadius;
    float kernelFactor = 0.5f;

    int max_neighbors;

    int particlesX;
    int particlesY;
    int particlesZ;
    int num_particles;

    float domainX = 20.0f;
    float domainY = 40.0f;
    float domainZ = 20.0f;

    float rest_density = 10.0;
    float mass = 5.0;

    glm::vec3 gravity = glm::vec3(0, -10.0, 0.0);
    float time_step = 0.01;
    float steps = 4;

    float relaxation_epsilon = 10.0f;

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

extern float poly6_kernel(const Simulation* simulation, float r);
extern float poly6_kernel(const Simulation* simulation, glm::vec3& r);
extern glm::vec3 spiky_kernel(const Simulation* simulation, glm::vec3& r);


extern void simulate(Simulation* simulation);