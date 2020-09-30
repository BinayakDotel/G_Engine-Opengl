#pragma once
#include <detail\setup.hpp>
#include <fwd.hpp>
#include <vector>
#include <tiny_gltf.h>

struct m_BufferView {
	int target;
	unsigned int byteLength;
	//struct tinygltf::Buffer const* buffer;
	const void * buffer;
	unsigned int offset;
	//class std::vector<unsigned char, class std::allocator<unsigned char> > const* test;
};
struct m_Draw {
	int mode;
	size_t count;
	int c_type;
	const void* offset;
};
