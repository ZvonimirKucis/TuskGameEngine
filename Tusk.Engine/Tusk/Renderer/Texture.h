#pragma once

#include <string>
#include <vulkan/vulkan.h>

namespace Tusk {

	class VulkanDevice;
	class VulkanCommand;

	class Texture {
	public:
		virtual ~Texture() {}

		virtual void bind(VulkanDevice* device, VulkanCommand* command) = 0;

		virtual VkImageView getTextureImageView() = 0;
		virtual VkSampler getTextureSampler() = 0;

		static Ref<Texture> create(const std::string& textureFile);
	};
}