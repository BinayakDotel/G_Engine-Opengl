#pragma once
#include <glm.hpp>
#include <array>
#include <GLTFData.h>

class BufferData {
private:
	unsigned int vbo_id;

public:
	BufferData(m_BufferView m_buffer);
	~BufferData();
	
	void bindBufferData();

	void unBindBufferData()const;

	void set_vbo_id(unsigned int id);
	unsigned int get_vbo_id();
};
