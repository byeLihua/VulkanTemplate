#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vulkan/vulkan_raii.hpp>

#include "window.hpp"

class Application {
 private:
  Window* window;

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
