#include <Texture.h>
#include <stb_image.h>
#include <Error.h>

Texture::Texture(const std::string& path)
	: m_renderer_id(0), img_filepath(path),
	img_localBuffer(nullptr), img_width(0),
	img_height(0), img_bpp(0)

{
	stbi_set_flip_vertically_on_load(1);
	img_localBuffer = stbi_load(path.c_str(), &img_width, &img_height, &img_bpp, 4);
	if (img_localBuffer == NULL) {
		print("Texture not loaded");
	}
	GLCALL(glGenTextures(1, &m_renderer_id));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_renderer_id));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_localBuffer));

	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

	if (img_localBuffer) {
		stbi_image_free(img_localBuffer);
	}
}
Texture :: ~Texture() {
	GLCALL(glDeleteTextures(1, &m_renderer_id));
}
void Texture::bindTexture(unsigned int slot) const {
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
}
void Texture::unbindTexture() const {
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}
