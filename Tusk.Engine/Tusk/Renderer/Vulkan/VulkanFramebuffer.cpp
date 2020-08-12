#include "tuskpch.h"

#include "VulkanFramebuffer.h"

namespace Tusk {

	VulkanFramebuffer::VulkanFramebuffer(VulkanDevice* device, VulkanSwapChain* swapchain, VulkanPipeline* pipeline, VulkanDepthBuffer* depthBuffer)
		: _device(device), _swapchain(swapchain), _pipeline(pipeline), _depthBuffer(depthBuffer) {
		Logger::Trace("Initializing Vulkan framebuffers.");
		createFramebuffers();
	}

	void VulkanFramebuffer::createFramebuffers() {
		auto swapChainImageViews = _swapchain->getSwapChainImageViews();
		auto swapChainExtent = _swapchain->getSwapChainExtent();
		auto renderPass = _pipeline->getRenderPass();
		auto depthImageView = _depthBuffer->getDepthImageView();

		_swapChainFramebuffers.resize(swapChainImageViews.size());

		for (size_t i = 0; i < swapChainImageViews.size(); i++) {
			std::array<VkImageView, 2> attachments = {
				swapChainImageViews[i],
				depthImageView
			};

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = renderPass;
			framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
			framebufferInfo.pAttachments = attachments.data();
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