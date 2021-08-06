#pragma once

#include "../buffer/VertexBuffer.hpp"
#include "../layout/VertexBufferLayout.hpp"

namespace Levek {
class VertexArray
{
private:
	unsigned int renderer_id;
	unsigned int attrib_id;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	//void AddInstancedBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;

};
}