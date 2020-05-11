#include "VertexArray.h"
#include "Error.h"
#include "print.h"
#include <Vertex.h>

VertexArray::VertexArray() {
	GLCALL(glGenVertexArrays(1, &m_renderer_id));
}
VertexArray::~VertexArray() {
	GLCALL(glDeleteVertexArrays(1, &m_renderer_id));
}
void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	bindVertexArray();
	const auto& elements = layout.getElement();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalize, layout.getStride(), (const void*) offset));
		offset += element.count * VertexBufferLayout::GetSizeOfType(element.type);
	}
}
void VertexArray::bindVertexArray() const {
	GLCALL(glBindVertexArray(m_renderer_id));
}
void VertexArray::unbindVertexArray() const {
	GLCALL(glBindVertexArray(0));
}