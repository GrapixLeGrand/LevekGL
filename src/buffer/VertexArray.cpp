#include "VertexArray.hpp"
#include "../OpenGLError.hpp"
#include "../renderer/Renderer.hpp"

namespace Levek {

VertexArray::VertexArray() : attrib_id(0) {
	GL_CHECK(glGenVertexArrays(1, &renderer_id));
	GL_CHECK(glBindVertexArray(renderer_id)); //before was renderer_id
}

VertexArray::~VertexArray() {
	GL_CHECK(glDeleteVertexArrays(1, &renderer_id));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	/*bind();
	vb.bind(); //bind the vertex buffer
	//then we set up the layout
	const auto& elements = layout.getElements();
	unsigned long long offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		
		const auto& element = elements[i];
		GL_CHECK(glEnableVertexAttribArray(attrib_id)); //index of the attribute array
		GL_CHECK(glVertexAttribPointer(attrib_id, element.count, element.type, element.normalized, layout.getStride(), (const void *) offset));
		if (element.instances) {
			GL_CHECK(glVertexAttribDivisor(attrib_id, element.instances));
		}
		offset += (unsigned long long) element.count * VertexBufferElement::getSizeOfType(element.type);
		this->attrib_id++;

	}*/

	//unbind(); //added this to debug
	//vb.unbind();
	addBuffer(&vb, &layout);
	
}

void VertexArray::addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout) {
	bind();
	vb->bind(); //bind the vertex buffer

	mVerticesNum = vb->getSize() / layout->getStride();

	//then we set up the layout
	const auto& elements = layout->getElements();
	unsigned long long offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		
		const auto& element = elements[i];
		GL_CHECK(glEnableVertexAttribArray(attrib_id)); //index of the attribute array
		
		if (element.type == GL_UNSIGNED_INT) { //for integral type we must use another attrib pointer
			GL_CHECK(glVertexAttribIPointer(attrib_id, element.count, element.type, layout->getStride(), (const void *) offset));
		} else {
			GL_CHECK(glVertexAttribPointer(attrib_id, element.count, element.type, element.normalized, layout->getStride(), (const void *) offset));
		}

		if (element.instanceDivisor) {
			GL_CHECK(glVertexAttribDivisor(attrib_id, element.instanceDivisor));
		}
		offset += (unsigned long long) element.count * VertexBufferElement::getSizeOfType(element.type);
		this->attrib_id++;

	}

	//unbind(); //added this to debug
	//vb.unbind();
	
}

/*
void VertexArray::AddInstancedBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	bind();
	vb.bind();
	const auto& elements = layout.getInstancedElements();
	unsigned long long offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {

		const auto& element = elements[i];
		GL_CHECK(glEnableVertexAttribArray(attrib_id)); //index of the attribute array
		GL_CHECK(glVertexAttribPointer(attrib_id, element.count, element.type, element.normalized, layout.getInstancedStride(), (const void*) offset));
		GL_CHECK(glVertexAttribDivisor(attrib_id, 1));
		offset += (unsigned long long) element.count * VertexBufferElement::getSizeOfType(element.type);
		this->attrib_id++;

	}
}*/

void VertexArray::bind() const {
	GL_CHECK(glBindVertexArray(renderer_id));
}

void VertexArray::unbind() const {
	GL_CHECK(glBindVertexArray(0));
}

}