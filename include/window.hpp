#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <cstdint>
#include <vulkan/vulkan_raii.hpp>

class Window {
 public:
  virtual vk::raii::SurfaceKHR getSurface();

  virtual void setTitle(const char* title);
  virtual void setWidth(uint16_t width);
  virtual void setHeight(uint16_t height);

  /**
   * return
   * false: window has be closed
   * true: else
   */
  virtual bool update();
};

#endif  // WINDOW_HPP
