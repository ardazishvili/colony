#include "figImpl/ColonyApplication.h"

int main(int argc, char** argv)
{
  try {
    ColonyApplication app;
    app.run();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
