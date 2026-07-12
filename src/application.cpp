#include "application.hpp"

Application::Application() {}

Application::~Application() {}

bool Application::update() {
  bool isRunning = true;
  if (!_window.update()) {
    isRunning = false;
  }
  return isRunning;
}
