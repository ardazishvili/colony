#include "fig/Log.h"

#include "figImpl/ColonyApplication.h"

int main(int argc, char** argv)
{
  try {
    ColonyApplication app;
    app.init();
    app.run();
    Log::logCore(Level::Trace, "tracing message");
    Log::logCore(Level::Error, "error message");

    Log::logApp(Level::Warn, "warning message");
    Log::logApp(Level::Critical, "critical message");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
