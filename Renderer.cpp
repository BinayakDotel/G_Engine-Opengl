#include <Renderer.h>
#include <Error.h>

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	shader.bindShader();
	va.bindVertexArray();
	GLCALL(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
void Renderer::clearScreen() const {
	GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCALL(glClearColor(0.3f, 0.4f, 0.9f, 1.0f));
	GLCALL(glEnable(GL_DEPTH_TEST));
	GLCALL(glDepthFunc(GL_ALWAYS));
}
