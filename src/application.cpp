#include "application.hpp"

#ifdef _WIN32
#include "platform/windows/window_windows.hpp"
#endif

Application::Application() {
#ifdef _WIN32
  _window = new WindowWindows();
  _vkManager = new VkManager();
#endif
}

Application::~Application() {
  delete (_vkManager);
  delete (_window);
}

bool Application::update() {
  bool isRunning = true;
  if (!_window->update()) {
    isRunning = false;
  }
  return isRunning;
}
