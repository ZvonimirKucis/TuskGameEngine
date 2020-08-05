#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace Tusk {
	
	class VulkanDevice;

	class VulkanInstance {
	public:
		VulkanInstance();
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

		VkInstance _instance;
		VkDebugUtilsMessengerEXT _debugMessenger;
		VkSurfaceKHR _surface;
		VulkanDevice* _device;
	};
}