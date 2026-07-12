#include "vk_manager.hpp"

VkManager::VkManager() { createInstance(); }

VkManager::~VkManager() {}

void VkManager::createInstance() {
  vk::ApplicationInfo appInfo{.apiVersion = vk::ApiVersion14};
  vk::InstanceCreateInfo createInfo{.pApplicationInfo = &appInfo};
  createInfo.setPEnabledLayerNames(enableLayerNames);
  _instance = vk::raii::Instance(_context, createInfo);
}
