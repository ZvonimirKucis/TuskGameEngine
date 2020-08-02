#include "VulkanUtils.h"

namespace Tusk {
	
	void VulkanUtils::detectQueueFamilyIndices(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, I32* graphicsQueueIndex, I32* presentationQueueIndex) {
        U32 queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> familyProperties(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, familyProperties.data());

        for (U32 i = 0; i < queueFamilyCount; ++i) {

            if (familyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                *graphicsQueueIndex = i;
            }

            VkBool32 supportsPresentation = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &supportsPresentation);
            if (supportsPresentation) {
                *presentationQueueIndex = i;
            }
        }
	}

}