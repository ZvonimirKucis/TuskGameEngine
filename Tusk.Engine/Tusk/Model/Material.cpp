#include "tuskpch.h"

#include "Material.h"

namespace Tusk {
	Material::Material(const Ref<Shader>& shader)
		: _materialShader(shader){}

	void Material::set2DTexture(const Ref<Texture2D>& texture) {
		_textures.push_back(texture);
	}

	void Material::bindTextures() {
		for (uint32_t i = 0; i < _textures.size(); i++) {
			std::string name = Texture::toString(_textures[i]->getType());
			_materialShader->setInt((name).c_str(), i);
			_textures[i]->bind(i);
		}
	}
}