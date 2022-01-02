#pragma once

#include "../buffer/VertexBuffer.hpp"
#include "../layout/VertexBufferLayout.hpp"

namespace Levek {
class VertexArray
{
private:
	unsigned int renderer_id;
	unsigned int attrib_id;
	size_t mVerticesNum = 0;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout);

	//void AddInstancedBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;
	size_t getVerticesNum() const {
		return mVerticesNum;
	}

};
}