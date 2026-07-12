#ifndef VK_MANAGER_HPP
#define VK_MANAGER_HPP

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>

class VkManager {
 private:
  const std::array<const char*, 1> enableLayerNames = {
      "VK_LAYER_KHRONOS_validation"};

  vk::raii::Context _context;
  vk::raii::Instance _instance = nullptr;
  vk::raii::Device _device = nullptr;

  void createInstance();
  void createDevice();

 public:
  VkManager();
  ~VkManager();
};

#endif  // VK_MANAGER_HPP
