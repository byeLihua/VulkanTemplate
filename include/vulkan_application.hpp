#ifndef VULKAN_APPLICATION
#define VULKAN_APPLICATION

#include <vulkan/vulkan_raii.hpp>

#include "window.hpp"

class VulkanApplication {
 private:
  Window* window;

 public:
  VulkanApplication();
  ~VulkanApplication();

  /**
   * return
   * false: Application quit
   * true: else
   */
  bool update();
};

#endif  // VULKAN_APPLICATION
