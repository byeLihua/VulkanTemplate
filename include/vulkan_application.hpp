#ifndef VULKAN_APPLICATION
#define VULKAN_APPLICATION

#include <vulkan/vulkan_raii.hpp>

#include "window.hpp"

class VulkanApplication {
 private:
  Window window;

 public:
  VulkanApplication();
  ~VulkanApplication();
};

#endif  // VULKAN_APPLICATION
