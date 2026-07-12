#include "application.hpp"

#ifdef _WIN32
#include "platform/windows/window_windows.hpp"
#endif

Application::Application() {
#ifdef _WIN32
  window = new WindowWindows();
#endif
}

Application::~Application() { delete (window); }

bool Application::update() {
  bool isRunning = true;
  if (!window->update()) {
    isRunning = false;
  }
  return isRunning;
}
