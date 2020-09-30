#include "VertexArray.h"
#include "Error.h"
#include "print.h"
#include <Vertex.h>

VertexArray::VertexArray(){
	vao_id= 0;
}
VertexArray::~VertexArray() {
	GLCALL(glDeleteVertexArrays(1, &vao_id));
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
	GLCALL(glBindVertexArray(vao_id));
}
void VertexArray::unbindVertexArray() const {
	GLCALL(glBindVertexArray(0));
}
void VertexArray::set_vao_id(unsigned int id) {
	this->vao_id= id;
}
unsigned int VertexArray::get_vao_id() const {
	return vao_id;
}