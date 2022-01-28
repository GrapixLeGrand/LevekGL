#pragma once

#include <GL/glew.h>

namespace Levek {
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
    unsigned int instanceDivisor; //the attrib divisor argument

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		//ASSERT(false); to manage circlar dependency
		return 0;
	}
};
}