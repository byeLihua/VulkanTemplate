#include "vulkan_application.hpp"

#ifdef _WIN32
#include "platform/windows/window_windows.hpp"
#endif

VulkanApplication::VulkanApplication() {
#ifdef _WIN32
  window = new WindowWindows();
#endif
}

VulkanApplication::~VulkanApplication() { delete (window); }

bool VulkanApplication::update() {
  bool isRunning = true;
  if (!window->update()) {
    isRunning = false;
  }
  return isRunning;
}
