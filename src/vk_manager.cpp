#include "vk_manager.hpp"

VkManager::VkManager(Window* window) {
  createInstance();
  _surface = window->createSurface(&_instance);
  createDevice();
}

VkManager::~VkManager() {}

void VkManager::createInstance() {
  vk::ApplicationInfo appInfo{.apiVersion = vk::ApiVersion14};
  auto createInfo =
      vk::InstanceCreateInfo{.pApplicationInfo = &appInfo}
          .setPEnabledLayerNames(_enableInstanceLayerNames)
          .setPEnabledExtensionNames(_enableInstanceExtensionNames);
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
      vk::DeviceCreateInfo{}
          .setQueueCreateInfos(deviceQueueCreateInfos)
          .setPEnabledExtensionNames(_enableDeviceExtensionNames);
  _device = vk::raii::Device(physicalDevice, deviceCreateInfo);

  // create swapchain
  vk::PhysicalDeviceSurfaceInfo2KHR surfaceInfo{.surface = _surface};
  auto surfaceCapabilities =
      physicalDevice.getSurfaceCapabilities2KHR(surfaceInfo);
  auto surfaceFormats = physicalDevice.getSurfaceFormats2KHR(surfaceInfo);
  auto surfacePresentModes = physicalDevice.getSurfacePresentModesKHR(_surface);
  vk::SwapchainCreateInfoKHR swapchainCreateInfo{
      .surface = _surface,
      .minImageCount = surfaceCapabilities.surfaceCapabilities.minImageCount,
      .imageFormat = vk::Format::eB8G8R8A8Srgb,
      .imageColorSpace = vk::ColorSpaceKHR::eSrgbNonlinear,
      .imageExtent = surfaceCapabilities.surfaceCapabilities.currentExtent,
      .imageArrayLayers = 1,
      .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
      .imageSharingMode = vk::SharingMode::eExclusive,
      .preTransform = surfaceCapabilities.surfaceCapabilities.currentTransform,
      .compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque,
      .presentMode = vk::PresentModeKHR::eFifo,
      .clipped = true};
  _swapchain = vk::raii::SwapchainKHR(_device, swapchainCreateInfo);
}
