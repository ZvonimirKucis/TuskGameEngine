#pragma once

#include "../Renderer/Shader.h"

namespace Tusk {

	class Material {
	public:
		Material() = default;

		bool isLoaded() { return _loaded; }
		Shader* getShader() { return _shader; }

	private:
		void createShader();
		void loadTextures();

	private:
		bool _loaded = false;
		Shader* _shader;
	};

}