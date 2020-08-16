#pragma once

#include "../GraphicsContext.h"

struct GLFWwindow;

namespace Tusk {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow* _windowHandle;
	};

}