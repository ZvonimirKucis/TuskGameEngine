#include "tuskpch.h"

#include "OpenGLCubemap.h"

#include <stb_image.h>

#include <glad/glad.h>

namespace Tusk {

	OpenGLCubemap::OpenGLCubemap(const std::vector<std::string> faces) {
		glGenTextures(1, &_rendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _rendererID);
		stbi_set_flip_vertically_on_load(false);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++) {
			stbi_uc* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
			}
			else {
				stbi_image_free(data);
				Logger::Fatal("Cubemap tex failed to load at path: %s", faces[i].c_str());
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void OpenGLCubemap::bind() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _rendererID);
	}

	OpenGLCubemap::~OpenGLCubemap() {
		glDeleteTextures(1, &_rendererID);
	}

}