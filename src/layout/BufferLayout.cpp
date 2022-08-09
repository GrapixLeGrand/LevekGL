#include "BufferLayout.hpp"

#include <GL/glew.h>
#include <cassert>

namespace Levek {

	unsigned int VertexBufferElement::getSizeOfType(unsigned int type) {
		switch (type) {
		case GL_UNSIGNED_SHORT: return 2;
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		//ASSERT(false); to manage circlar dependency
		assert(false && "You may have forgot to define a type size\n");
		return 0;
	}
};