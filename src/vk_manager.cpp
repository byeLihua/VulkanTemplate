#include "vk_manager.hpp"

#include <fstream>

VkManager::VkManager(Window* window) {
  createInstance();
  _surface = window->createSurface(&_instance);
  createDevice();
  createPipline();
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

  // choose a physical device
  for (const vk::raii::PhysicalDevice& each : physicalDevices) {
    vk::PhysicalDeviceProperties2 physicalDeviceProperties =
        each.getProperties2();
    if (vk::PhysicalDeviceType::eDiscreteGpu ==
        physicalDeviceProperties.properties.deviceType) {
      _physicalDevice = vk::raii::PhysicalDevice(std::move(each));
    }
  }

  // choose a queue family
  const float queuePriority = 0.5f;
  std::array<vk::DeviceQueueCreateInfo, 1> deviceQueueCreateInfos{};
  std::vector<vk::QueueFamilyProperties2> queueFamilyProperties =
      _physicalDevice.getQueueFamilyProperties2();
  for (uint16_t index = 0; index < queueFamilyProperties.size(); index++) {
    if (queueFamilyProperties[index].queueFamilyProperties.queueFlags &
        vk::QueueFlagBits::eGraphics) {
      deviceQueueCreateInfos[0].queueFamilyIndex = index;
      deviceQueueCreateInfos[0].queueCount = 1;
      deviceQueueCreateInfos[0].pQueuePriorities = &queuePriority;
      break;
    }
  }

  vk::PhysicalDeviceVulkan13Features deviceFeature{.dynamicRendering =
                                                       vk::True};
  auto deviceCreateInfo =
      vk::DeviceCreateInfo{.pNext = &deviceFeature}
          .setQueueCreateInfos(deviceQueueCreateInfos)
          .setPEnabledExtensionNames(_enableDeviceExtensionNames);
  _device = vk::raii::Device(_physicalDevice, deviceCreateInfo);

  // create swapchain
  vk::PhysicalDeviceSurfaceInfo2KHR surfaceInfo{.surface = _surface};
  auto surfaceCapabilities =
      _physicalDevice.getSurfaceCapabilities2KHR(surfaceInfo);
  vk::SwapchainCreateInfoKHR swapchainCreateInfo{
      .surface = _surface,
      .minImageCount = surfaceCapabilities.surfaceCapabilities.minImageCount,
      .imageFormat = _imageFormat,
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

void VkManager::createPipline() {
  auto shaderCodeFile = std::ifstream("../../shader/shader.spv",
                                      std::ios::ate | std::ios::binary);
  std::vector<char> shaderCodeBuffer(shaderCodeFile.tellg());
  shaderCodeFile.seekg(0, std::ios::beg);
  shaderCodeFile.read(shaderCodeBuffer.data(), shaderCodeBuffer.size());
  shaderCodeFile.close();
  vk::ShaderModuleCreateInfo shaderModuleCreateInfo{
      .codeSize = shaderCodeBuffer.size() * sizeof(char),
      .pCode = reinterpret_cast<uint32_t*>(shaderCodeBuffer.data())};
  auto shaderModule = vk::raii::ShaderModule(_device, shaderModuleCreateInfo);

  vk::PipelineShaderStageCreateInfo vertexStageCreateInfo{
      .stage = vk::ShaderStageFlagBits::eVertex,
      .module = shaderModule,
      .pName = "vertexMain"};
  vk::PipelineShaderStageCreateInfo fragmentStageCreateInfo{
      .stage = vk::ShaderStageFlagBits::eFragment,
      .module = shaderModule,
      .pName = "fragmentMain"};
  vk::PipelineShaderStageCreateInfo shaderStageCreateInfo[] = {
      vertexStageCreateInfo, fragmentStageCreateInfo};

  vk::PipelineVertexInputStateCreateInfo vertexInputStateCreateInfo{};

  vk::PipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo{
      .topology = vk::PrimitiveTopology::eTriangleList};

  vk::PhysicalDeviceSurfaceInfo2KHR surfaceInfo{.surface = _surface};
  auto surfaceCapabilities =
      _physicalDevice.getSurfaceCapabilities2KHR(surfaceInfo);
  vk::Viewport viewport{
      .x = 0,
      .y = 0,
      .width =
          (float)surfaceCapabilities.surfaceCapabilities.currentExtent.width,
      .height =
          (float)surfaceCapabilities.surfaceCapabilities.currentExtent.height,
      .minDepth = 0,
      .maxDepth = 1};
  vk::Rect2D scissor{
      .offset = vk::Offset2D{0, 0},
      .extent = surfaceCapabilities.surfaceCapabilities.currentExtent};
  auto viewportStateCreateInfo =
      vk::PipelineViewportStateCreateInfo{}.setViewports(viewport).setScissors(
          scissor);

  vk::PipelineRasterizationStateCreateInfo rasterizationStateCreateInfo{
      .depthClampEnable = vk::False,
      .rasterizerDiscardEnable = vk::False,
      .polygonMode = vk::PolygonMode::eFill,
      .cullMode = vk::CullModeFlagBits::eBack,
      .frontFace = vk::FrontFace::eClockwise,
      .depthBiasClamp = vk::False,
      .lineWidth = 1};

  vk::PipelineMultisampleStateCreateInfo multisampleStateCreateInfo{
      .rasterizationSamples = vk::SampleCountFlagBits::e1,
      .sampleShadingEnable = vk::False};

  vk::PipelineColorBlendAttachmentState colorBlendAttachmentState{
      .blendEnable = vk::False,
      .colorWriteMask =
          vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
          vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA};
  auto ColorBlendStateCreateInfo =
      vk::PipelineColorBlendStateCreateInfo{.logicOpEnable = vk::False,
                                            .logicOp = vk::LogicOp::eCopy}
          .setAttachments(colorBlendAttachmentState);

  vk::PipelineLayoutCreateInfo layoutCreateInfo{.setLayoutCount = 0,
                                                .pushConstantRangeCount = 0};
  vk::raii::PipelineLayout pipelineLayout(_device, layoutCreateInfo);

  auto graphicsPipelineCreateInfo =
      vk::GraphicsPipelineCreateInfo{
          .pVertexInputState = &vertexInputStateCreateInfo,
          .pInputAssemblyState = &inputAssemblyStateCreateInfo,
          .pViewportState = &viewportStateCreateInfo,
          .pRasterizationState = &rasterizationStateCreateInfo,
          .pMultisampleState = &multisampleStateCreateInfo,
          .pColorBlendState = &ColorBlendStateCreateInfo,
          .pDynamicState = nullptr,
          .layout = pipelineLayout,
          .renderPass = nullptr}
          .setStages(shaderStageCreateInfo);
  auto renderingCreateInfo =
      vk::PipelineRenderingCreateInfo{}.setColorAttachmentFormats(_imageFormat);
  vk::StructureChain<vk::GraphicsPipelineCreateInfo,
                     vk::PipelineRenderingCreateInfo>
      pipelineCreateInfoChain{graphicsPipelineCreateInfo, renderingCreateInfo};

  _pipeline = vk::raii::Pipeline(
      _device, nullptr,
      pipelineCreateInfoChain.get<vk::GraphicsPipelineCreateInfo>());
}
