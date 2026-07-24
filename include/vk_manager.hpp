#ifndef VK_MANAGER_HPP
#define VK_MANAGER_HPP

#include <vulkan/vulkan_raii.hpp>

#include "window.hpp"

class VkManager {
 private:
  const std::array<const char*, 1> _enableInstanceLayerNames = {
      "VK_LAYER_KHRONOS_validation"};
  const std::array<const char*, 3> _enableInstanceExtensionNames = {
      "VK_KHR_surface", "VK_KHR_win32_surface",
      "VK_KHR_get_surface_capabilities2"};
  const std::array<const char*, 2> _enableDeviceExtensionNames = {
      "VK_KHR_swapchain", "VK_KHR_shader_draw_parameters"};
  const vk::Format _imageFormat = vk::Format::eB8G8R8A8Srgb;

  vk::raii::Context _context;
  vk::raii::Instance _instance = nullptr;
  vk::raii::PhysicalDevice _physicalDevice = nullptr;
  vk::raii::Device _device = nullptr;
  vk::raii::SurfaceKHR _surface = nullptr;
  vk::raii::SwapchainKHR _swapchain = nullptr;
  vk::raii::Pipeline _pipeline = nullptr;

  void createInstance();
  void createDevice();
  void createPipline();

 public:
  VkManager() = delete;
  VkManager(Window* window);
  ~VkManager();
};

#endif  // VK_MANAGER_HPP
