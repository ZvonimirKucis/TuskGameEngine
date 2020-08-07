#include "tuskpch.h"

#include "Shader.h"
#include "Vulkan/VulkanShader.h"

namespace Tusk{

	Ref<Shader> Shader::create(const std::string& vertexFile, const std::string& fragmentFile) {
		return CreateRef<VulkanShader>(vertexFile, fragmentFile);
	}

}