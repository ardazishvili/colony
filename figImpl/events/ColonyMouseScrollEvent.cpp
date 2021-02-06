#include "ColonyMouseScrollEvent.h"
#include "../../fig/Camera.h"

ColonyMouseScrollEvent::ColonyMouseScrollEvent(double xoffset, double yoffset) : MouseScrollEvent(xoffset, yoffset)
{
}

void ColonyMouseScrollEvent::process(fig::Camera* camera, fig::EventManager* m)
{
  camera->zoom(_yoffset);
}
