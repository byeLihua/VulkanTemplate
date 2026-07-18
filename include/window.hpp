#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <cstdint>
#include <vulkan/vulkan_raii.hpp>

/**
 * every platform-based window class rewrite this class as interface
 */
class Window {
 public:
  virtual vk::raii::SurfaceKHR createSurface(vk::raii::Instance* instance) = 0;

  virtual void setTitle(const char* title) = 0;
  virtual void setWidth(uint16_t width) = 0;
  virtual void setHeight(uint16_t height) = 0;

  /**
   * return
   * false: window has be closed
   * true: else
   */
  virtual bool update() = 0;
};

#endif  // WINDOW_HPP
