#include "BufferLayout.hpp"

#include <GL/glew.h>

namespace Levek {

	unsigned int VertexBufferElement::getSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		//ASSERT(false); to manage circlar dependency
		return 0;
	}
};