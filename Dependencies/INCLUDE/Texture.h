#pragma once

#include <Renderer.h>

class Texture {
private:
	unsigned int m_renderer_id;
	const std::string& img_filepath;
	unsigned char* img_localBuffer;
	int img_width, img_height, img_bpp;

public:
	Texture(const std::string& path);
	~Texture();

	void bindTexture(unsigned int slot = 0) const;
	void unbindTexture() const;

	inline int getWidth() const { return img_width; }
	inline int getHeight() const { return img_height; }
	inline const std::string& getPath() const { return img_filepath; }
};