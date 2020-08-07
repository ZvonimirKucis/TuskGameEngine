#pragma once

#include <vulkan/vulkan.h>
#include "../../Utils/Defines.h"

#define VK_CHECK(expr) { ASSERT(expr == VK_SUCCESS) }

#ifdef NDEBUG
const bool ENABLE_VALIDATION_LAYERS = false;
#else
#include <vector>
const bool ENABLE_VALIDATION_LAYERS = true;

const std::vector<const char*> requiredValidationLayers = {
    "VK_LAYER_KHRONOS_validation"
};
#endif

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};