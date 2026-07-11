#include "vulkan_application.hpp"

int main(int argc, char** argv) {
  VulkanApplication application = VulkanApplication();
  while (application.update()) {
  }
  return 0;
}
