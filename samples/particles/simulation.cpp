#include "simulation.hpp"

#include <cmath>
#include <iostream>
#include <utility>
#include <algorithm>

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

    simulation->W = cubic_kernel;
    simulation->gradW = cubic_kernel_grad;

    //for the kernel
    float h3 = std::pow(simulation->kernelRadius, 3);
    simulation->cubic_kernel_k = 8.0 / (pi * h3);
    simulation->cubic_kernel_l = 48.0 / (pi * h3);

    //sorting neighbor strategy with grid
    simulation->cell_size = simulation->kernelRadius;
    simulation->gridX = (int) (simulation->domainX / simulation->cell_size);
    simulation->gridY = (int) (simulation->domainY / simulation->cell_size);
    simulation->gridZ = (int) (simulation->domainZ / simulation->cell_size);

    simulation->num_grid_cells = (simulation->gridX + 2) * (simulation->gridY + 2) * (simulation->gridZ + 2);
    simulation->particle_cell_index_to_index = std::vector<std::pair<int, int>>(simulation->num_particles, std::make_pair(0, 0));
    simulation->positions_star_copy = std::vector<glm::vec3>(simulation->num_particles, {0, 0, 0});
    simulation->cell_indices = std::vector<std::pair<int, int>>(simulation->num_grid_cells, std::make_pair(0, 0));

}

void fill_grid(Simulation* simulation) {

    int X = simulation->particlesX;
    int Y = simulation->particlesY;
    int Z = simulation->particlesZ;

    float diameter = simulation->particleDiameter;
    float radius = simulation->particleRadius;
    glm::vec3 offset = glm::vec3(radius, radius, radius);

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

void clear_neighbors(Simulation* simulation) {
    for (int i = 0; i < simulation->num_particles; i++) {
        simulation->neighbors[i].clear();
    }
}

void find_neighbors(Simulation* simulation) {

    clear_neighbors(simulation);

    for (int i = 0; i < simulation->num_particles; i++) {
        glm::vec3& self = simulation->positions_star[i];
        for (int j = i + 1; j < simulation->num_particles; j++) {
            glm::vec3& other = simulation->positions_star[j];
            glm::vec3 tmp = self - other;
            if (glm::dot(tmp, tmp) <= simulation->kernelRadius * simulation->kernelRadius) {
                simulation->neighbors[i].push_back(j);
                simulation->neighbors[j].push_back(i);
            }
        }
    }

}


float cubic_kernel(const Simulation* simulation, float r) {
    float q = (r * simulation->kernelFactor) / simulation->kernelRadius;
    float result = 0.0;
    if (q <= 1.0) {
        if (q <= 0.5) {
            float q2 = q * q;
            float q3 = q2 * q;
            result = simulation->cubic_kernel_k * (6.0f * q3 - 6.0f * q2 + 1.0f);
        } else {
            result = simulation->cubic_kernel_k * (2.0f * std::pow(1.0f - q, 3.0f));
        }
    }
    return result;
}

float cubic_kernel(const Simulation* simulation, glm::vec3& r) {
    float tmp = glm::length(r);
    return cubic_kernel(simulation, tmp);
}

glm::vec3 cubic_kernel_grad(const Simulation* simulation, const glm::vec3& r) {
    glm::vec3 result = glm::vec3(0.0);
    float rl = glm::length(r) * simulation->kernelFactor;
    float q = rl / simulation->kernelRadius;

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

float poly6_kernel(const Simulation* simulation, float r) {
    float result = 0.0;
    float hf = simulation->kernelRadius * simulation->kernelFactor;
    if (r <= simulation->kernelRadius) {
        result = (315.0f / (64.0f * 3.14f * std::pow(hf, 9))) * 
            std::pow(std::pow(hf, 2) - std::pow(simulation->kernelFactor * r, 2), 3);
    }
    return result;
}

float poly6_kernel(const Simulation* simulation, glm::vec3& r) {
    return poly6_kernel(simulation, r.length());
}

glm::vec3 spiky_kernel(const Simulation* simulation, glm::vec3& r) {
    glm::vec3 result = glm::vec3(0.0);
    float rl = glm::length(r);
    if (rl > 0.0 && rl <= simulation->kernelRadius) {
        float hf = simulation->kernelRadius * simulation->kernelFactor;
        float temp = ((15.0f / (3.14f * std::pow(hf, 6))) * 
            std::pow(hf - (rl * simulation->kernelFactor), 2));
        result = (r / (rl * simulation->kernelFactor)) * temp;
    }
    return result;
}

float s_coor(const Simulation* simulation, float rl) {
    return - simulation->s_corr_k * std::pow(simulation->W(simulation, rl) / simulation->W(simulation, simulation->s_corr_dq), simulation->s_corr_n);
}

float epsilon_collision = 0.01;

float resolve_collision(float value, float min, float max) {
    
    if (value <= min) {
        return epsilon_collision;
    }

    if (value > max) {
        return max - epsilon_collision;
    }

    return value;
}

glm::vec3 get_cell_id_comp(const Simulation* simulation, int i) {
    glm::vec3 position = simulation->positions_star[i];
    glm::clamp(position, glm::vec3(0.0), glm::vec3(simulation->domainX, simulation->domainY, simulation->domainZ));
    position /= simulation->cell_size;
    position.x = (int) position.x;
    position.y = (int) position.y;
    position.z = (int) position.z;
    return position;
}

int get_cell_id(const Simulation* simulation, int i) {

    glm::vec3 position = simulation->positions_star[i];
    glm::clamp(position, glm::vec3(0.0), glm::vec3(simulation->domainX, simulation->domainY, simulation->domainZ));
    position /= simulation->cell_size;
    //position += 1;
    /*
    int cell_id =
            simulation->gridY * simulation->gridZ + 
            ((int) position.x) * simulation->gridY * simulation->gridZ +
            simulation->gridZ + 
            ((int) position.y) * simulation->gridZ +
            1 +
            ((int) position.z);*/
    int cell_id =
            ((int) position.x) * simulation->gridY * simulation->gridZ +
            ((int) position.y) * simulation->gridZ +
            ((int) position.z);

    return cell_id;
}

void assign_particles_to_cells(Simulation* simulation) {

    simulation->particle_cell_index_to_index.clear();

    for (int i = 0; i < simulation->num_particles; i++) {

        int cell_id = get_cell_id(simulation, i);
        simulation->particle_cell_index_to_index.push_back(std::make_pair(cell_id, i));

    }

}

bool check_index(int i, int min, int max) {
    return (i >= min && i < max);
}

void find_neighbors_counting_sort(Simulation* simulation) {

    assign_particles_to_cells(simulation);
    std::sort(simulation->particle_cell_index_to_index.begin(), simulation->particle_cell_index_to_index.end(), 
        [] (const auto& p1, const auto& p2)
        {
            return p1.first < p2.first;
        }
    );

    simulation->positions_star_copy = simulation->positions_star;

    int startPos = 0;
    int current = 0;

    //copy particles in sorted order and update cells pointers
    for (int i = 0; i < simulation->num_particles; i++) {
        auto& p = simulation->particle_cell_index_to_index[i];
        simulation->positions_star[i] = simulation->positions_star_copy[p.second];

        if (current != p.first || i == simulation->num_particles - 1) { //new cell id encountered or we reached the end and no change
            if (i - startPos > 0) {
                simulation->cell_indices[current].first = startPos;
                simulation->cell_indices[current].second = i; //exclusive index
                if ((i == (simulation->num_particles - 1)) && current == p.first) {  //if we reached the end and nothing changed
                    simulation->cell_indices[current].second++;
                }
            } else {
                simulation->cell_indices[current].first = startPos;
                simulation->cell_indices[current].second = startPos; //we want the same number (nothing in the cell)
            }
            startPos = i;
            current = p.first;
        }
    }

    clear_neighbors(simulation);

    for (int i = 0; i < simulation->num_particles; i++) {
        const glm::vec3& self = simulation->positions_star[i];
        glm::vec3 indices = get_cell_id_comp(simulation, i);
        int xx = indices.x;
        int yy = indices.y;
        int zz = indices.z;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                for (int z = -1; z <= 1; z++) {
                    
                    if (
                        check_index(xx + x, 0, simulation->gridX) == false ||
                        check_index(yy + y, 0, simulation->gridY) == false ||
                        check_index(zz + z, 0, simulation->gridZ) == false
                    )
                    {
                        continue;
                    }

                    int neighor_cell_id = 
                        (x + xx) * simulation->gridY * simulation->gridZ +
                        (y + yy) * simulation->gridZ +
                        (z + zz);

                    const auto& range = simulation->cell_indices[neighor_cell_id];
                    int lower = range.first;
                    int upper = range.second;
                    for (int k = lower; k < upper; k++) {
                        if (k == i) continue;
                        const glm::vec3& other = simulation->positions_star[k];
                        const glm::vec3 tmp = self - other;
                        if (glm::dot(tmp, tmp) <= simulation->kernelRadius * simulation->kernelRadius) {
                            simulation->neighbors[i].push_back(k);
                        }
                    }

                }
            }
        }

    }
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

    //integration
    for (int i = 0; i < n; i++) {
        velocities[i] += simulation->gravity * simulation->mass * dt;
        positions_star[i] = positions[i] + velocities[i] * dt; //prediction
    }

    find_neighbors_counting_sort(simulation);
    //find_neighbors(simulation);

    //solve pressure
    for (int i = 0; i < n; i++) {

        float densitiy = 0.0;
        for (int j = 0; j < neighbors[i].size(); j++) {
            glm::vec3 ij = positions_star[i] - positions_star[neighbors[i][j]];
            float len = glm::length(ij);
            densitiy += simulation->mass * simulation->W(simulation, len);
        }
        densitiy += simulation->mass * simulation->W(simulation, 0.0);

        //equation 1
        float constraint_i = (densitiy / simulation->rest_density) - 1.0;
        float constraint_gradient_sum = 0.0;
        glm::vec3 grad_current_p = glm::vec3(0.0);

        //equation 8
        for (int j = 0; j < neighbors[i].size(); j++) {
            glm::vec3 temp = positions_star[i] - positions_star[neighbors[i][j]];
            glm::vec3 neighbor_grad = - (simulation->mass / simulation->rest_density) * simulation->gradW(simulation, temp);
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
            pressures_forces[i] += (lambdas[i] + lambdas[j] + s_coor(simulation, glm::length(ij))) * simulation->gradW(simulation, ij);
        }

        pressures_forces[i] /= simulation->rest_density;
        
        //update prediction
        positions_star[i] += pressures_forces[i];

        //update velocity
        positions_star[i].x = resolve_collision(positions_star[i].x, simulation->particleRadius, X - simulation->particleRadius);
        positions_star[i].y = resolve_collision(positions_star[i].y, simulation->particleRadius, Y - simulation->particleRadius);
        positions_star[i].z = resolve_collision(positions_star[i].z, simulation->particleRadius, Z - simulation->particleRadius);

        velocities[i] = (positions_star[i] - positions[i]) / simulation->time_step;
        positions[i] = positions_star[i];

    }



}