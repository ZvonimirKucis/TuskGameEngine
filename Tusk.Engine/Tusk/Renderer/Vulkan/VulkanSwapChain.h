#pragma once

#include <vulkan/vulkan.h>

namespace Tusk {

	class VulkanDevice;
	class Window;

	class VulkanSwapChain {
	public:
		VulkanSwapChain(VulkanDevice* device, const Ref<Window> window, VkSurfaceKHR surface);
		~VulkanSwapChain();

		VkSwapchainKHR getSwapChain() { return _swapChain; };
		VkExtent2D getSwapChainExtent() { return _swapChainExtent; }
		VkFormat getSwapChainImageFormat() { return _swapChainImageFormat; }
		std::vector<VkImageView> getSwapChainImageViews(){ return _swapChainImageViews; }

	private:
		void createSwapChain();

		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		void createImageViews();

	private:
		Ref<Window> _window;
		VulkanDevice* _device;
		VkSurfaceKHR _surface;

		VkSwapchainKHR _swapChain;
		std::vector<VkImage> _swapChainImages;
		VkFormat _swapChainImageFormat;
		VkExtent2D _swapChainExtent;
		std::vector<VkImageView> _swapChainImageViews;
	};
}

