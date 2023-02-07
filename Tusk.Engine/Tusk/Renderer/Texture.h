#pragma once

#include <string>

namespace Tusk {

	enum class TextureType {
		Empty = 0, Diffuse, Specular, Normal, Height
	};

	class Texture {
	public:
		virtual ~Texture() = default;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		virtual uint32_t getRendererID() const = 0;

		virtual void bind(uint32_t slot = 0) const = 0;

		virtual std::string getPath() const = 0;
		virtual TextureType getType() const = 0;

		static std::string toString(TextureType type) {
			switch (type) {
				case TextureType::Diffuse:
					return "texture_diffuse";
					break;
				case TextureType::Specular:
					return "texture_specular";
					break;
				case TextureType::Normal:
					return "texture_normal";
					break;
				case TextureType::Height:
					return "texture_height";
					break;
			}
		}
	};

	class Texture2D : public Texture {
	public:
		Texture2D() = default;

		static Ref<Texture2D> create(uint32_t width, uint32_t height);
		static Ref<Texture2D> create(const std::string& path, TextureType type, bool flip = false);
	};

}