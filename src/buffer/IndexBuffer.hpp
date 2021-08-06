#pragma once
#include "../OpenGLError.hpp"

namespace Levek {
class IndexBuffer {

	private:
		unsigned int rendererID;
		unsigned int count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count); // count == how many indices do we supply
		~IndexBuffer();
		void bind() const;
		void unbind() const;
		inline unsigned int GetCount() const { return count; }
};
}