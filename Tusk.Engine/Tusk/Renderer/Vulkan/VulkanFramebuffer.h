#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanPipeline.h"

namespace Tusk {
	class VulkanFramebuffer {
	public:
		VulkanFramebuffer(VulkanDevice* device, VulkanSwapChain* swapchain, VulkanPipeline* pipeline);
		~VulkanFramebuffer();

		std::vector<VkFramebuffer> getSwapChainFramebuffers() { return _swapChainFramebuffers; }

	private:
		void createFramebuffers();
	private:
		VulkanDevice* _device;
		VulkanSwapChain* _swapchain;
		VulkanPipeline* _pipeline;

		std::vector<VkFramebuffer> _swapChainFramebuffers;
	};
}