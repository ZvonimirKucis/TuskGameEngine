#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace Tusk {
	
	class Platform;
	class VulkanDevice;

	class VulkanRenderer {
	public:
		VulkanRenderer(Platform* platform);
		~VulkanRenderer();
	
	private:
		void initVulkan();
		void createInstance();
		void setupDebugMessenger();
		void createSurface();
		void createDevice();

		std::vector<const char*> getRequiredExtensions();
		void checkValidationLayerSupport();

	private:
		Platform* _platform;

		VkInstance _instance;
		VkDebugUtilsMessengerEXT _debugMessenger;
		VkSurfaceKHR _surface;
		VulkanDevice* _device;
	};
}