#include "fig/Core.h"

#include "figImpl/ColonyApplication.h"
#include "figImpl/globals.h"

auto main(int argc, char** argv) -> int
{
  try {
    auto app = gApp();
    app->run();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
