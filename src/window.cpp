#include "window.hpp"

vk::raii::SurfaceKHR Window::getSurface() { return nullptr; }

void Window::setTitle(const char* title) {}

void Window::setWidth(uint16_t width) {}

void Window::setHeight(uint16_t height) {}

bool Window::update() { return true; }
