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
    simulation->pressures_forces = std::vector<glm::vec3>(simulation->num_particles, {0, 0, 0});

    simulation->densities = std::vector<float>(simulation->num_particles, 0);
    simulation->lambdas = std::vector<float>(simulation->num_particles, 0);

    simulation->vorticities = std::vector<glm::vec3>(simulation->num_particles, {0, 0, 0});

    simulation->neighbors = std::vector<std::vector<int>>(simulation->num_particles);
    simulation->colors = std::vector<glm::vec4>(simulation->num_particles, {0, 0, 0, 0});

    //for the kernel
    float h3 = std::pow(simulation->kernelRadius, 3);
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
            glm::vec3 tmp = self - other;
            if (glm::dot(tmp, tmp) <= kernelRadius * kernelRadius) {
                neighbors[i].push_back(j);
                neighbors[j].push_back(i);
            }
        }
    }

}

void clear_neighbors(Simulation* simulation) {
    for (int i = 0; i < simulation->neighbors.size(); i++) {
        simulation->neighbors[i].clear();
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

float cubic_kernel(const Simulation* simulation, glm::vec3& r) {
    return cubic_kernel(simulation, r.length());
}

glm::vec3 cubic_kernel_grad(const Simulation* simulation, const glm::vec3& r) {
    glm::vec3 result = glm::vec3(0.0);
    float rl = r.length();
    float q = rl / simulation->particleRadius;

    if (rl > 1.0e-5 && q <= 1.0) {
        const glm::vec3 grad_q = (1.0f / (rl * simulation->kernelRadius)) * r;
        if (q <= 0.5) {
            result = simulation->cubic_kernel_l * q * (3.0f * q - 2.0f) * grad_q;
        } else {
            const float f = 1.0f - q;
            result = simulation->cubic_kernel_l * (- f * f) * grad_q;
        }
    }
    return result;
}

float epsilon_collision = 0.1;

float resolve_collision(float value, float min, float max) {
    
    if (value <= min) {
        return epsilon_collision;
    }

    if (value > max) {
        return max - epsilon_collision;
    }

    return value;
}

void simulate(Simulation* simulation) {

    int n = simulation->num_particles;
    int X = simulation->domainX;
    int Y = simulation->domainY;
    int Z = simulation->domainZ;

    std::vector<glm::vec3>& positions = simulation->positions;
    std::vector<glm::vec3>& positions_star = simulation->positions_star;
    std::vector<glm::vec3>& velocities = simulation->velocities;
    std::vector<glm::vec3>& pressures_forces = simulation->pressures_forces;

    std::vector<float>& densities = simulation->densities;
    std::vector<float>& lambdas = simulation->lambdas;
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

        densities[i] = 0.0;
        for (int j = 0; j < neighbors[i].size(); j++) {
            glm::vec3 ij = positions_star[i] - positions_star[neighbors[i][j]];
            densities[i] += simulation->mass * cubic_kernel(simulation, ij);
        }
        densities[i] = simulation->mass * cubic_kernel(simulation, 0.0);

        //equation 1
        float constraint_i = (densities[i] / simulation->rest_density) - 1.0;
        float constraint_gradient_sum = 0.0;
        glm::vec3 grad_current_p = glm::vec3(0.0);

        //equation 8
        for (int j = 0; j < neighbors[i].size(); j++) {
            glm::vec3 neighbor_grad = - (simulation->mass / simulation->rest_density) * cubic_kernel_grad(simulation, positions_star[i] - positions_star[neighbors[i][j]]);
            constraint_gradient_sum += glm::dot(neighbor_grad, neighbor_grad);
            grad_current_p -= neighbor_grad;
        }

        constraint_gradient_sum += glm::dot(grad_current_p, grad_current_p);

        lambdas[i] = 0.0;
        if (constraint_gradient_sum > 0.0) {
            lambdas[i] = - constraint_i / (constraint_gradient_sum + simulation->relaxation_epsilon);
        }

    }

    
    for (int i = 0; i < n; i++) {

        //equation 13 (applying pressure force correction)
        pressures_forces[i] = glm::vec3(0.0);
        for (int j = 0; j < neighbors[i].size(); j++) {
            glm::vec3 ij = positions_star[i] - positions_star[neighbors[i][j]];
            pressures_forces[i] += (lambdas[i] + lambdas[j]) * cubic_kernel_grad(simulation, ij);
        }

        pressures_forces[i] /= simulation->rest_density;
        
        //update prediction
        positions_star[i] += pressures_forces[i];

        //update velocity
        positions_star[i].x = resolve_collision(positions_star[i].x, 0, X);
        positions_star[i].y = resolve_collision(positions_star[i].y, 0, Y);
        positions_star[i].z = resolve_collision(positions_star[i].z, 0, Z);

        velocities[i] = (positions_star[i] - positions[i]) / simulation->time_step;
        positions[i] = positions_star[i];

    }



}