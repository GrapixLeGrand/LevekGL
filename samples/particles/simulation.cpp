#include "simulation.hpp"

#include <cmath>
constexpr double pi = 3.14159265358979323846;

void init_sim(Simulation* simulation, int particlesX, int particlesY, int particlesZ) {

    simulation->particlesX = particlesX;
    simulation->particlesY = particlesY;
    simulation->particlesZ = particlesZ;
    simulation->num_particles = particlesX * particlesY * particlesZ;

    simulation->max_neighbors = simulation->num_particles - 1;

    simulation->positions = std::vector<glm::vec3>(simulation->num_particles, {0, 0, 0});
    simulation->positions_star = std::vector<glm::vec3>(simulation->num_particles, {0, 0, 0});
    simulation->velocities = std::vector<glm::vec3>(simulation->num_particles, {0, 0, 0});

    simulation->densities = std::vector<float>(simulation->num_particles, 0);
    simulation->lambdas = std::vector<float>(simulation->num_particles, 0);

    simulation->vorticities = std::vector<glm::vec3>(simulation->num_particles, {0, 0, 0});

    simulation->neighbors = std::vector<std::vector<int>>(simulation->num_particles);
    simulation->colors = std::vector<glm::vec4>(simulation->num_particles, {0, 0, 0, 0});

    //for the kernel
    float h3 = std::pow(simulation->particleRadius, 3);
    simulation->cubic_kernel_k = 8.0 / (pi * h3);
    simulation->cubic_kernel_l = 48.0 / (pi * h3);

}

void fill_grid(Simulation* simulation) {

    int X = simulation->particlesX;
    int Y = simulation->particlesY;
    int Z = simulation->particlesZ;

    float diameter = simulation->particleDiameter;
    float radius = simulation->particleRadius;
    glm::vec3 offset = glm::vec3(0, radius, 0);

    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            for (int z = 0; z < Z; z++) {
                
                glm::vec3& position = simulation->positions[x * Y * Z + y * Z + z];
                glm::vec4& color = simulation->colors[x * Y * Z + y * Z + z];

                position.x = x * diameter;
                position.y = y * diameter; 
                position.z = z * diameter; 

                color.r = position.x / X;
                color.g = position.y / Y;
                color.b = position.z / Z;
                color.a = 1.0f;

                position += offset;

            }
        }
    }

}


void find_neighbors(Simulation* simulation) {

    std::vector<glm::vec3>& positions = simulation->positions;
    std::vector<std::vector<int>>& neighbors = simulation->neighbors;
    float kernelRadius = simulation->kernelRadius;

    for (int i = 0; i < simulation->num_particles; i++) {
        glm::vec3& self = positions[i];
        for (int j = i + 1; j < simulation->num_particles; j++) {
            glm::vec3& other = positions[j];
            if (glm::dot(self, other) <= kernelRadius) {
                neighbors[i].push_back(j);
            }
        }
    }

}

void clear_neighbors(Simulation* simulation) {
    std::vector<std::vector<int>>& neighbors = simulation->neighbors;
    for (int i = 0; i < neighbors.size(); i++) {
        neighbors[i].clear();
    }
}

float cubic_kernel(const Simulation* simulation, float r) {
    float q = r / simulation->kernelRadius;
    float result = 0.0;
    if (q <= 1.0) {
        if (q <= 0.5) {
            float q2 = q * q;
            float q3 = q2 * q;
            result = simulation->cubic_kernel_k * (6.0 * q3 - 6.0 * q2 + 1.0);
        } else {
            result = simulation->cubic_kernel_k * (2.0 * std::pow(1.0 - q, 3.0));
        }
    }
    return result;
}

glm::vec3 cubic_kernel_grad(const Simulation* simulation, const glm::vec3& r) {
    glm::vec3 result = glm::vec3(0.0);
    float rl = r.norm();
    float q = rl / simulation->particleRadius;

    if (rl > 1.0e-5 && q <= 1.0) {

    }

}


void simulate(Simulation* simulation) {

    int n = simulation->num_particles;

    std::vector<glm::vec3>& positions = simulation->positions;
    std::vector<glm::vec3>& positions_star = simulation->positions_star;
    std::vector<glm::vec3>& velocities = simulation->velocities;
    std::vector<float>& densities = simulation->densities;
    std::vector<std::vector<int>>& neighbors = simulation->neighbors;
    float kernelRadius = simulation->kernelRadius;
    float dt = simulation->time_step;

    clear_neighbors(simulation);

    //integration
    for (int i = 0; i < n; i++) {
        velocities[i] += simulation->gravity * simulation->mass * dt;
        positions_star[i] = positions[i] + velocities[i] * dt;
    }

    find_neighbors(simulation);

    //solve pressure
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < neighbors[i].size(); j++) {
            densities[i] = simulation->mass *  
        }

    }


}