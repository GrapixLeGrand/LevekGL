#pragma once

#include "mesh/Mesh.hpp"
#include "../OpenGLError.hpp"

namespace Levek {
class IndexBuffer {

	private:
		unsigned int rendererID;
		unsigned int count;
	public:

		/**
		 * @brief Construct a new Index Buffer object
		 * 
		 * @param data 
		 * @param count the number of indices (not the size in bytes!)
		 */
		IndexBuffer(const unsigned int* data, unsigned int count); // count == how many indices do we supply
		IndexBuffer(const Mesh*);
		~IndexBuffer();
		void bind() const;
		void unbind() const;
		inline unsigned int GetCount() const { return count; }
};
}