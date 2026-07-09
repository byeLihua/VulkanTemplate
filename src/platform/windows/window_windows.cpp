#include "platform/windows/window_windows.hpp"

LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

WindowWindows::WindowWindows() { _createWindow(); }

WindowWindows::~WindowWindows() { _destroyWindow(); }

void WindowWindows::_createWindow() {
  _hInstance = GetModuleHandle(NULL);

  // register window class
  const wchar_t* windowName = L"VulkanApplication";
  WNDCLASS windowClass{};
  windowClass.lpfnWndProc = windowProc;
  windowClass.hInstance = _hInstance;
  windowClass.lpszClassName = _windowClassName;
  RegisterClass(&windowClass);

  _hWnd = CreateWindow(_windowClassName, windowName,
                       WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
                       _hInstance, NULL);
}

void WindowWindows::_destroyWindow() {
  DestroyWindow(_hWnd);
  UnregisterClass(_windowClassName, _hInstance);
}

LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

vk::SurfaceKHR WindowWindows::getSurface() { return nullptr; }

void WindowWindows::setTitle(const char* title) {}

void WindowWindows::setWidth(const uint16_t width) {}

void WindowWindows::setHeight(const uint16_t height) {}
