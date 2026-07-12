#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vulkan/vulkan_raii.hpp>

#include "vk_manager.hpp"
#include "window.hpp"

class Application {
 private:
  Window* _window;
  VkManager* _vkManager;

 public:
  Application();
  ~Application();

  /**
   * return
   * false: Application quit
   * true: else
   */
  bool update();
};

#endif  // APPLICATION_HPP
