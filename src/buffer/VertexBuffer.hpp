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
		VertexBuffer();
		VertexBuffer(const Mesh* mesh);
		VertexBuffer(const void* data, unsigned int size);
		VertexBuffer(const void* data, size_t size);
		VertexBuffer(const void* data, unsigned int size, unsigned int usage);

		template<typename T>
		VertexBuffer(const std::vector<T>& data) : VertexBuffer(data.data(), data.size() * sizeof(T)) {};

		~VertexBuffer();
		void update(const void* data, unsigned int size);

		template<typename T>
		void update(const std::vector<T>* data) {
			update(data->data(), data->size() * sizeof(T));
		}

		template<typename T>
		void update(const std::vector<T>& data) {
			update(data.data(), data.size() * sizeof(T));
		}

		void bind() const;
		void unbind() const;

		size_t getSize() const {
			return (size_t) size;
		}

};
}