#pragma once

#include "../Texture.h"

namespace Tusk {

	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path, TextureType type, bool flip);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth() const override { return _width;  }
		virtual uint32_t getHeight() const override { return _height; }
		virtual uint32_t getRendererID() const override { return _rendererID; }

		virtual void bind(uint32_t slot = 0) const override;

		virtual TextureType getType() const override { return _type; }
		virtual std::string getPath() const override { return _path; }

	private:
		uint32_t _width, _height;
		uint32_t _rendererID;
		std::string _path;
		TextureType _type;
	};

}
