#include "application.hpp"

Application::Application() : _window(), _vkManager(&_window) {}

Application::~Application() {}

bool Application::update() {
  bool isRunning = true;
  if (!_window.update()) {
    isRunning = false;
  }
  return isRunning;
}
