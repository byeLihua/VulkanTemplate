#include <iostream>

#include "vulkan_application.hpp"

int main(int argc, char** argv) {
  VulkanApplication* pApplication = new VulkanApplication();
  delete (pApplication);
  return 0;
}
