#ifndef VK_MANAGER_HPP
#define VK_MANAGER_HPP

#include <vulkan/vulkan_raii.hpp>

#include "window.hpp"

class VkManager {
 private:
  const std::array<const char*, 1> _enableLayerNames = {
      "VK_LAYER_KHRONOS_validation"};
  const std::array<const char*, 2> _enableExtensionNames = {
      "VK_KHR_surface", "VK_KHR_win32_surface"};

  vk::raii::Context _context;
  vk::raii::Instance _instance = nullptr;
  vk::raii::Device _device = nullptr;
  vk::raii::SurfaceKHR _surface = nullptr;

  void createInstance();
  void createDevice();

 public:
  VkManager() = delete;
  VkManager(Window* window);
  ~VkManager();
};

#endif  // VK_MANAGER_HPP
