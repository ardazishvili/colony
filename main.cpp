#include "fig/Log.h"

#include "figImpl/ColonyApplication.h"

int main(int argc, char** argv)
{
  try {
    ColonyApplication app;
    app.init();
    app.run();
    FG_CORE_TRACE("tracing message");
    FG_CORE_ERROR("error message");

    FG_APP_WARN("warning message");
    FG_APP_CRITICAL("critical message");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
