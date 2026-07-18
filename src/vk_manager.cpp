#include "vk_manager.hpp"

VkManager::VkManager(Window* window) {
  createInstance();
  createDevice();
  _surface = window->createSurface(&_instance);
}

VkManager::~VkManager() {}

void VkManager::createInstance() {
  vk::ApplicationInfo appInfo{.apiVersion = vk::ApiVersion14};
  auto createInfo = vk::InstanceCreateInfo{.pApplicationInfo = &appInfo}
                        .setPEnabledLayerNames(_enableLayerNames)
                        .setPEnabledExtensionNames(_enableExtensionNames);
  _instance = vk::raii::Instance(_context, createInfo);
}

void VkManager::createDevice() {
  vk::raii::PhysicalDevices physicalDevices(_instance);
  vk::raii::PhysicalDevice physicalDevice = nullptr;

  // choose a physical device
  for (const vk::raii::PhysicalDevice& each : physicalDevices) {
    vk::PhysicalDeviceProperties2 physicalDeviceProperties =
        each.getProperties2();
    if (vk::PhysicalDeviceType::eDiscreteGpu ==
        physicalDeviceProperties.properties.deviceType) {
      physicalDevice = vk::raii::PhysicalDevice(std::move(each));
    }
  }

  // choose a queue family
  const float queuePriority = 0.5f;
  std::array<vk::DeviceQueueCreateInfo, 1> deviceQueueCreateInfos{};
  std::vector<vk::QueueFamilyProperties2> queueFamilyProperties =
      physicalDevice.getQueueFamilyProperties2();
  for (uint16_t index = 0; index < queueFamilyProperties.size(); index++) {
    if (queueFamilyProperties[index].queueFamilyProperties.queueFlags &
        vk::QueueFlagBits::eGraphics) {
      deviceQueueCreateInfos[0].queueFamilyIndex = index;
      deviceQueueCreateInfos[0].queueCount = 1;
      deviceQueueCreateInfos[0].pQueuePriorities = &queuePriority;
      break;
    }
  }

  auto deviceCreateInfo =
      vk::DeviceCreateInfo{}.setQueueCreateInfos(deviceQueueCreateInfos);
  _device = vk::raii::Device(physicalDevice, deviceCreateInfo);
}
