#include "ColonyMouseScrollEvent.h"
#include "../../fig/Camera.h"

ColonyMouseScrollEvent::ColonyMouseScrollEvent(double xoffset, double yoffset) :
  MouseScrollEvent(xoffset, yoffset)
{
}

void ColonyMouseScrollEvent::process(Camera* camera, EventManager* m)
{
  camera->zoom(_yoffset);
}
