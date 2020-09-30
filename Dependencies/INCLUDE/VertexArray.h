#pragma once

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>

class VertexArray {
private:
	unsigned int vao_id;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bindVertexArray() const;
	void unbindVertexArray() const;
	void set_vao_id(unsigned int id);
	unsigned int get_vao_id() const;
};
