#pragma once

#include "Tusk/Renderer/Cubemap.h"

namespace Tusk {

	class OpenGLCubemap : public Cubemap {
	public:
		OpenGLCubemap(const std::vector<std::string> faces);
		virtual ~OpenGLCubemap();

		virtual void bind() override;

	private:
		uint32_t _rendererID;

	};

}