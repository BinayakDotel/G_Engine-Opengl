#pragma once
#include <vector>
#include <Error.h>
#include <print.h>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalize;
};
class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		:m_Stride(0) {}

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 2;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}

	template<typename T>
	void push(unsigned int count) {
		static_assert(false);
	}
	template<>
	void push<float>(unsigned int count) {
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferLayout::GetSizeOfType(GL_FLOAT);
		print(count);
	}
	template<>
	void push<unsigned int>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferLayout::GetSizeOfType(GL_UNSIGNED_INT);
	}
	template<>
	void push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferLayout::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement>& getElement() const { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; };
};

