#pragma once

#include <vector>
#include "BufferLayout.hpp"

namespace Levek {
class VertexBufferLayoutInstancing {
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride; 
public:

	VertexBufferLayoutInstancing(): stride(0) {}

	template<typename T>
	void push(unsigned int count) {}

	inline const std::vector<VertexBufferElement> getElements() const& { return elements; }
	inline unsigned int getStride() const { return stride; }
};
}