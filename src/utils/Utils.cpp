
#include "utils/Utils.hpp"

namespace Levek {

void printMat4(const glm::mat4& m) {
    printf(
        "[[%.4f, %.4f, %.4f, %.4f]\n"
        " [%.4f, %.4f, %.4f, %.4f]\n"
        " [%.4f, %.4f, %.4f, %.4f]\n"
        " [%.4f, %.4f, %.4f, %.4f]]\n", 
        m[0][0],
        m[1][0],
        m[2][0],
        m[3][0],

        m[0][1],
        m[1][1],
        m[2][1],
        m[3][1],

        m[0][2],
        m[1][2],
        m[2][2],
        m[3][2],

        m[0][3],
        m[1][3],
        m[2][3],
        m[3][3]

    );
}
/*
extern void printMat4(const glm::mat4& m) {
    std::cout << 
        m[0][0] << "\t" << m[1][0] << "\t" << m[2][0] << "\t" << m[3][0] << "\n" <<
        m[0][1] << "\t" << m[1][1] << "\t" << m[2][1] << "\t" << m[3][1] << "\n" <<
        m[0][2] << "\t" << m[1][2] << "\t" << m[2][2] << "\t" << m[3][2] << "\n" <<
        m[0][3] << "\t" << m[1][3] << "\t" << m[2][3] << "\t" << m[3][3] << "\n" << std::endl;
} */

extern void printMat3(const glm::mat3& m) {
    std::cout << 
        m[0][0] << "\t" << m[1][0] << "\t" << m[2][0] << "\n" <<
        m[0][1] << "\t" << m[1][1] << "\t" << m[2][1] << "\n" <<
        m[0][2] << "\t" << m[1][2] << "\t" << m[2][2] << "\n" << std::endl;
} 

extern void printVec3(const glm::vec3& v) {
    printf("[%f, %f, %f]\n", v[0], v[1], v[2]);
} 
};