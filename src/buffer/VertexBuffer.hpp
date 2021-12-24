#pragma once

#include "mesh/Mesh.hpp"
#include <stddef.h>

namespace Levek {
	/*
	enum BufferUsage { //TODO use this
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW
	};*/
class VertexBuffer {

	private:
		unsigned int rendererID; //internal renderer ID, relevant to OpenGl
		unsigned int size;
		unsigned int usage;
	public:
		VertexBuffer(Mesh* mesh);
		VertexBuffer(const void* data, unsigned int size);
		VertexBuffer(const void* data, size_t size);
		VertexBuffer(const void* data, unsigned int size, unsigned int usage);
		~VertexBuffer();
		void Update(const void* data, unsigned int size);
		void bind() const;
		void unbind() const;

};
}