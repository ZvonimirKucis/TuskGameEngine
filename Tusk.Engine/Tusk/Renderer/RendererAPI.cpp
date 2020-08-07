#include "tuskpch.h"
#include "RendererAPI.h"

#include "Vulkan/VulkanRendererAPI.h"

namespace Tusk {

	Scope<RendererAPI> RendererAPI::create()
	{ 
		return CreateScope<VulkanRendererAPI>();
	}
}