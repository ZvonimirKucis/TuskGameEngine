#pragma once

#include <vulkan/vulkan.h>
#include "../Texture.h"
#include "VulkanDevice.h"
#include "VulkanCommand.h"

namespace Tusk {
	class VulkanImageHelper {
	public:
		static void createImage(VulkanDevice* device, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		static void transitionImageLayout(VulkanCommand* command, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		static void copyBufferToImage(VulkanCommand* command, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
		static VkImageView createImageView(VulkanDevice* device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	};

	class VulkanTexture : public Texture {
	public:
		VulkanTexture(const std::string& textureFile);
		virtual ~VulkanTexture();

		virtual void bind(VulkanDevice* device, VulkanCommand* command) override;

		virtual VkImageView getTextureImageView() override { return _textureImageView; }
		virtual VkSampler getTextureSampler() override { return _textureSampler; }

	private:
		void createTextureImage();
		void createTextureImageView();
		void createTextureSampler();
	private:
		std::string _textureFile;
		VulkanDevice* _device;
		VulkanCommand* _command;

		VkImage _textureImage = VK_NULL_HANDLE;
		VkDeviceMemory _textureImageMemory;
		VkImageView _textureImageView;
		VkSampler _textureSampler;
	};
}