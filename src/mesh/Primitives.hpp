#pragma once

#include "Mesh.hpp"

namespace Levek {


extern float planeVertices[4 * 3];
extern float planeTex[4 * 2];
extern float planeNormal[2 * 3];
extern unsigned int planeIndices[2 * 3];

extern Mesh makePlane(float width, float height, int divisions);

};