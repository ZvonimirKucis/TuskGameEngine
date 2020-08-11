#include "tuskpch.h"
#include "Texture.h"

#include "Vulkan/VulkanTexture.h"

namespace Tusk {

	Ref<Texture> Texture::create(const std::string& textureFile) {
		return CreateRef<VulkanTexture>(textureFile);
	}
}