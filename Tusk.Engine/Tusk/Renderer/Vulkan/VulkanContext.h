#pragma once

#include "../GraphicsContext.h"

struct GLFWwindow;

namespace Tusk {
	
	class VulkanContext : public GraphicsContext {
	public:
		VulkanContext(GLFWwindow* window);

		virtual void init() override;
		virtual void swapBuffers() override;

	private:
		GLFWwindow* _window;
	};
}