#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanPipeline.h"
#include "VulkanDepthBuffer.h"

namespace Tusk {
	class VulkanFramebuffer {
	public:
		VulkanFramebuffer(VulkanDevice* device, VulkanSwapChain* swapchain, VulkanPipeline* pipeline, VulkanDepthBuffer* depthBuffer);
		~VulkanFramebuffer();

		std::vector<VkFramebuffer> getSwapChainFramebuffers() { return _swapChainFramebuffers; }

	private:
		void createFramebuffers();
	private:
		VulkanDevice* _device;
		VulkanSwapChain* _swapchain;
		VulkanPipeline* _pipeline;
		VulkanDepthBuffer* _depthBuffer;

		std::vector<VkFramebuffer> _swapChainFramebuffers;
	};
}