#include "tuskpch.h"
#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Tusk {

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: _width(width), _height(height) {

		glCreateTextures(GL_TEXTURE_2D, 1, &_rendererID);
		glTextureStorage2D(_rendererID, 1, GL_RGBA, _width, _height);

		glTextureParameteri(_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, TextureType type)
		: _path(path), _type(type){
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		ASSERT_MSG(data, "Failed to load image!");
	
		_width = width;
		_height = height;

		GLenum format = 0;
		if (channels == 4){
			format = GL_RGBA;
		} else if (channels == 3) {
			format = GL_RGB;
		} else if (channels == 1) {
			format = GL_RED;
		}

		glGenTextures(1, &_rendererID);
		glBindTexture(GL_TEXTURE_2D, _rendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &_rendererID);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const {
		//glActiveTexture(GL_TEXTURE0 + slot);
		//glBindTexture(GL_TEXTURE_2D, _rendererID);
		glBindTextureUnit(slot, _rendererID);
	}
}