#include "tuskpch.h"

#include "../../Utils/Logger.h"#
#include "VulkanFramebuffer.h"

namespace Tusk {

	VulkanFramebuffer::VulkanFramebuffer(VulkanDevice* device, VulkanSwapChain* swapchain, VulkanPipeline* pipeline)
		: _device(device), _swapchain(swapchain), _pipeline(pipeline) {
		Logger::Trace("Initializing Vulkan framebuffers.");
		createFramebuffers();
	}

	void VulkanFramebuffer::createFramebuffers() {
		auto swapChainImageViews = _swapchain->getSwapChainImageViews();
		auto swapChainExtent = _swapchain->getSwapChainExtent();
		auto renderPass = _pipeline->getRenderPass();

		_swapChainFramebuffers.resize(swapChainImageViews.size());

		for (size_t i = 0; i < swapChainImageViews.size(); i++) {
			VkImageView attachments[] = {
				swapChainImageViews[i]
			};

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = renderPass;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = swapChainExtent.width;
			framebufferInfo.height = swapChainExtent.height;
			framebufferInfo.layers = 1;

			VK_CHECK(vkCreateFramebuffer(_device->getDevice(), &framebufferInfo, nullptr, &_swapChainFramebuffers[i]))
		}
	}

	VulkanFramebuffer::~VulkanFramebuffer() {
		for (auto framebuffer : _swapChainFramebuffers) {
			vkDestroyFramebuffer(_device->getDevice(), framebuffer, nullptr);
		}
	}
}