
#include "utils/Utils.hpp"

namespace Levek {

extern void printMat4(const glm::mat4& m) {
    std::cout << 
        m[0][0] << "\t" << m[1][0] << "\t" << m[2][0] << "\t" << m[3][0] << "\n" <<
        m[0][1] << "\t" << m[1][1] << "\t" << m[2][1] << "\t" << m[3][1] << "\n" <<
        m[0][2] << "\t" << m[1][2] << "\t" << m[2][2] << "\t" << m[3][2] << "\n" <<
        m[0][3] << "\t" << m[1][3] << "\t" << m[2][3] << "\t" << m[3][3] << "\n" << std::endl;
} 

extern void printMat3(const glm::mat3& m) {
    std::cout << 
        m[0][0] << "\t" << m[1][0] << "\t" << m[2][0] << "\n" <<
        m[0][1] << "\t" << m[1][1] << "\t" << m[2][1] << "\n" <<
        m[0][2] << "\t" << m[1][2] << "\t" << m[2][2] << "\n" << std::endl;
} 

extern void printVec3(const glm::vec3& v) {
    std::cout << 
        v[0] << "\t" << v[1] << "\t" << v[2] << "\n" << std::endl;
} 
};