#ifndef WINDOW_WINDOWS
#define WINDOW_WINDOWS

#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>

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

  vk::raii::SurfaceKHR getSurface() override;
  void setTitle(const char* title) override;
  void setWidth(const uint16_t width) override;
  void setHeight(const uint16_t height) override;

  bool update() override;
};

#endif  // WINDOW_WINDOWS
