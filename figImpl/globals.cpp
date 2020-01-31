#include "globals.h"
#include "ColonyApplication.h"

Application<SpdBackend>* gApp()
{
  static auto app = std::make_unique<ColonyApplication<SpdBackend>>();
  return app.get();
}
