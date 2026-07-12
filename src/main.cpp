#include "application.hpp"

int main(int argc, char** argv) {
  Application application = Application();
  while (application.update()) {
  }
  return 0;
}
