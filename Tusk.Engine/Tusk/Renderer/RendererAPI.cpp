#include "tuskpch.h"
#include "RendererAPI.h"

#include "Vulkan/VulkanRendererAPI.h"

namespace Tusk {

	RendererAPI::API RendererAPI::_API = RendererAPI::API::Vulkan;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (_API)
		{
			case RendererAPI::API::None:    
				return nullptr;
			case RendererAPI::API::Vulkan:  
				return CreateScope<VulkanRendererAPI>();
		}

		return nullptr;
	}

}