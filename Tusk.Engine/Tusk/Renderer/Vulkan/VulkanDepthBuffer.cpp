#include "tuskpch.h"

#include "VulkanDepthBuffer.h"
#include "VulkanTexture.h"

namespace Tusk {

	VulkanDepthBuffer::VulkanDepthBuffer(VulkanDevice* device, VulkanSwapChain* swapchain) {
		_device = device;
		_swapchain = swapchain;

		createDepthResources();
	}

	void VulkanDepthBuffer::createDepthResources() {
		auto swapChainExtent = _swapchain->getSwapChainExtent();
		VkFormat depthFormat = findSupportedFormat(
			{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
		);

		VulkanImageHelper::createImage(_device, swapChainExtent.width, swapChainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _depthImage, _depthImageMemory);
		_depthImageView = VulkanImageHelper::createImageView(_device, _depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
	}

	VkFormat VulkanDepthBuffer::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
		for (VkFormat format : candidates) {
			VkFormatProperties props;
			vkGetPhysicalDeviceFormatProperties(_device->getPhysicalDevice(), format, &props);

			if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
				return format;
			}
			else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
				return format;
			}
		}

		Logger::Fatal("Failed to find supported format!");
	}

	bool VulkanDepthBuffer::hasStencilComponent(VkFormat format) {
		return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
	}

	VulkanDepthBuffer::~VulkanDepthBuffer() {
		vkDestroyImageView(_device->getDevice(), _depthImageView, nullptr);
		vkDestroyImage(_device->getDevice(), _depthImage, nullptr);
		vkFreeMemory(_device->getDevice(), _depthImageMemory, nullptr);
	}

}