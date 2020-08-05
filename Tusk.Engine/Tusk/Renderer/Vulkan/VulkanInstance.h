#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#include "VulkanDevice.h"

namespace Tusk {
	
	class VulkanDevice;
	class Window;

	class VulkanInstance {
	public:
		VulkanInstance(const Ref<Window> window);
		~VulkanInstance();
	
	private:
		void initVulkan();
		void createInstance();
		void setupDebugMessenger();
		void createSurface();
		void createDevice();

		std::vector<const char*> getRequiredExtensions();
		void checkValidationLayerSupport();

	private:
		Ref<Window> _window;
		VkInstance _instance;
		VkDebugUtilsMessengerEXT _debugMessenger;
		VkSurfaceKHR _surface;
		VulkanDevice* _device;
	};
}