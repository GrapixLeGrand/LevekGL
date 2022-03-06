#pragma once

namespace Levek {
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
    unsigned int instanceDivisor; //the attrib divisor argument
	static unsigned int getSizeOfType(unsigned int type);
};
}