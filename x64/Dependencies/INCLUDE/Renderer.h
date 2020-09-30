#pragma once
#include <VertexArray.h>
#include <IndexBuffer.h>
#include <Shader.h>

class Renderer {
private:

public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

	void clearScreen() const;
};