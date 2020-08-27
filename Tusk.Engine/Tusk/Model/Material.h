#pragma once

#include "Tusk/Renderer/Shader.h"
#include "Tusk/Renderer/Texture.h"

namespace Tusk {
	class Material {
	public:
		Material(const Ref<Shader>& shader);

		Ref<Shader> getShader() { return _materialShader; }
		
		void set2DTexture(const Ref<Texture2D>& texture);

		void bindTextures();
	private:
		Ref<Shader> _materialShader;
		std::vector<Ref<Texture2D>> _textures;
	};

}