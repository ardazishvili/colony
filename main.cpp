#include "fig/Core.h"

#include "figImpl/ColonyApplication.h"
#include "figImpl/globals.h"

int main(int argc, char** argv)
{
  try {
    auto app = gApp();
    FG_APP_WARN("warning message")
    FG_APP_CRITICAL("critical message")
    auto a = 5;
    FG_APP_ERROR("printing example {0}", a)

    FG_CORE_WARN("warning message")
    FG_CORE_CRITICAL("critical message")
    auto b = 5;
    FG_CORE_ERROR("printing example {0}", b)

    app->run();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
