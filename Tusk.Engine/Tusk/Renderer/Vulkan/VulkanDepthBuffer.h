#pragma once

#include <vulkan/vulkan.h>
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"

namespace Tusk {

	class VulkanDepthBuffer {
	public:
		VulkanDepthBuffer(VulkanDevice* device, VulkanSwapChain* swapchain);
		~VulkanDepthBuffer();

		VkImageView getDepthImageView() { return _depthImageView; }

	private:
		void createDepthResources();
		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		bool hasStencilComponent(VkFormat format);
	private:
		VulkanDevice* _device;
		VulkanSwapChain* _swapchain;

		VkImage _depthImage;
		VkDeviceMemory _depthImageMemory;
		VkImageView _depthImageView;
	};
}
