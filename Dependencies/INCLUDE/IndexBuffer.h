#pragma once
#include <GLTFData.h>
#include <GLTFData.h>

class IndexBuffer {
private:
	unsigned int id;
	unsigned int m_count;
	m_BufferView m_buffer;

public:
	IndexBuffer(m_BufferView buffer);
	~IndexBuffer();

	void bindIndex() const;
	void unBindIndex() const;
	void deleteIndex() const;
	inline unsigned int getCount() const { return m_count; }
	unsigned int get_ibo_id() const;
};