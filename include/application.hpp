#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#ifdef _WIN32
#include "platform/windows/window_windows.hpp"
#endif
#include "vk_manager.hpp"

class Application {
 private:
#ifdef _WIN32
  WindowWindows _window;
#endif
  VkManager _vkManager;

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
