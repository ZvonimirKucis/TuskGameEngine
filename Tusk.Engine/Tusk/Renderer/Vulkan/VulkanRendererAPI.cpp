#include "tuskpch.h"

#include "VulkanRendererAPI.h"

namespace Tusk {

	void VulkanRendererAPI::init(const Ref<Window> window) {
		_instance = CreateScope<VulkanInstance>(window);
	}

	VulkanRendererAPI::~VulkanRendererAPI() {
	}
}