#include "vulkan_application.hpp"

#ifdef _WIN32
#include "platform/windows/window_windows.hpp"
#endif

VulkanApplication::VulkanApplication() {
#ifdef _WIN32
  window = WindowWindows();
#endif
}

VulkanApplication::~VulkanApplication() {}
