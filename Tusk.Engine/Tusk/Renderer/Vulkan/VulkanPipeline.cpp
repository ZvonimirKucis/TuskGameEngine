#include "tuskpch.h"

#include "../../Utils/Logger.h"

#include "VulkanPipeline.h"

namespace Tusk {

	VulkanPipeline::VulkanPipeline(VulkanDevice* device, VulkanSwapChain* swapchain)
		: _device(device), _swapchain(swapchain){
        Logger::Trace("Initializing Vulkan render pass and pipeline layout.");

        createRenderPass();
        createPipelineLayout();
	}

    void VulkanPipeline::createRenderPass() {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = _swapchain->getSwapChainImageFormat();
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;

        VK_CHECK(vkCreateRenderPass(_device->getDevice(), &renderPassInfo, nullptr, &_renderPass))
    }

    void VulkanPipeline::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pushConstantRangeCount = 0;

        VK_CHECK(vkCreatePipelineLayout(_device->getDevice(), &pipelineLayoutInfo, nullptr, &_pipelineLayout))
    }

/*void VulkanPipeline::createGraphicsPipeline(VkShaderModule vertShaderModule, VkShaderModule fragShaderModule) {
        
    }*/

	VulkanPipeline::~VulkanPipeline() {
		vkDestroyPipelineLayout(_device->getDevice(), _pipelineLayout, nullptr);
        vkDestroyRenderPass(_device->getDevice(), _renderPass, nullptr);
	}
}