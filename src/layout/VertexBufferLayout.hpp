#pragma once

#include <vector>
#include <type_traits>

#include "../OpenGLError.hpp"

#include "BufferLayout.hpp"
//#include <GL/glew.h>
//#include "ErrorManager.h"
#include "glm/glm.hpp"


/*
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		//ASSERT(false); to manage circlar dependency
		return 0;
	}
};*/

/*
	Class to maintain elements in our vertex buffer
	What is the layout of our buffer
*/
namespace Levek {

class VertexBufferLayout
{
private:
	size_t mSizeOfVertex = 0;
	std::vector<VertexBufferElement> elements;
	//std::vector<VertexBufferElement> instancedElements;
	unsigned int stride; 
	//unsigned int instancedStride;
public:

	VertexBufferLayout(): stride(0) /*, instancedStride(0)*/ {}
	template<typename K> void push(unsigned int count, unsigned int instances);
	template<typename T> void push(unsigned int count);

	inline const std::vector<VertexBufferElement> getElements() const& { return elements; }
	//inline const std::vector<VertexBufferElement> getInstancedElements() const& { return instancedElements; }
	inline unsigned int getStride() const { return stride; }
	
	size_t getSizeOfVertex() const {
		return mSizeOfVertex;
	}

	//inline unsigned int getInstancedStride() const { return instancedStride; }

};
}