#ifndef WINDOW_WINDOWS_HPP
#define WINDOW_WINDOWS_HPP

#include <windows.h>

#include <vulkan/vulkan_raii.hpp>

#include "window.hpp"

class WindowWindows : public Window {
 private:
  const wchar_t* _windowClassName = L"VulkanApplicationWindowClass";
  HINSTANCE _hInstance;
  HWND _hWnd;

  void _createWindow();
  void _destroyWindow();

 public:
  WindowWindows();
  ~WindowWindows();

  vk::raii::SurfaceKHR createSurface(vk::raii::Instance* instance) override;
  void setTitle(const char* title) override;
  void setWidth(const uint16_t width) override;
  void setHeight(const uint16_t height) override;

  bool update() override;
};

#endif  // WINDOW_WINDOWS_HPP
