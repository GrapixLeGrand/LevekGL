
#include "VertexBufferLayout.hpp"

/**
 * Implementation of the VertexBufferLayout
 */
namespace Levek {

    template<>
	void VertexBufferLayout::push<float>(unsigned int count, unsigned int instances) {
		elements.push_back({ GL_FLOAT, count, GL_FALSE, instances });
		this->stride +=  VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void VertexBufferLayout::push<unsigned int>(unsigned int count, unsigned int instances) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE, instances });
		this->stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void VertexBufferLayout::push<glm::vec2>(unsigned int count, unsigned int instances) {
		for (unsigned int i = 0; i < count; i++) {
			push<float>(2, instances);
		}
	}

	template<>
	void VertexBufferLayout::push<glm::vec3>(unsigned int count, unsigned int instances) {
		for (unsigned int i = 0; i < count; i++) {
			push<float>(3, instances);
		}
	}

	template<>
	void VertexBufferLayout::push<glm::vec4>(unsigned int count, unsigned int instances) {
		for (unsigned int i = 0; i < count; i++) {
			push<float>(4, instances);
		}
	}

	template<>
	void VertexBufferLayout::push<glm::mat3>(unsigned int count, unsigned int instances) {
		for (unsigned int i = 0; i < count; i++) {
			push<glm::vec3>(3, instances);
		}
	}

	template<>
	void VertexBufferLayout::push<glm::mat4>(unsigned int count, unsigned int instances) {
		for (unsigned int i = 0; i < count; i++) {
			push<glm::vec4>(4, instances);
		}
	}
	

    template<>
	void VertexBufferLayout::push<float>(unsigned int count) {
		elements.push_back({ GL_FLOAT, count, GL_FALSE, 0});
		stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count; //4 bytes
	}

	template<>
	void VertexBufferLayout::push<glm::vec2>(unsigned int count) {
		for (unsigned int i = 0; i < count; i++) {
			push<float>(2);
		}
	}

	template<> void VertexBufferLayout::push<glm::vec3>(unsigned int count) {
		for (unsigned int i = 0; i < count; i++) {
			push<float>(3);
		}
	}

	template<>
	void VertexBufferLayout::push<glm::vec4>(unsigned int count) {
		for (unsigned int i = 0; i < count; i++) {
			push<float>(4);
		}
	}

	template<>
	void VertexBufferLayout::push<glm::mat3>(unsigned int count) {
		for (unsigned int j = 0; j < count; j++) {
			push<glm::vec3>(3);
		}
	}

	template<>
	void VertexBufferLayout::push<glm::mat4>(unsigned int count) {
		for (unsigned int j = 0; j < count; j++) {
			push<glm::vec4>(4);
		}
	}

	template<>
	void VertexBufferLayout::push<unsigned int>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void VertexBufferLayout::push<unsigned char>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	/*
	template<> void VertexBufferLayout::p<glm::vec3>(glm::vec3 a) {
		LEVEK_RENDERING_INFO("Succeed !!!!");
	}*/
}