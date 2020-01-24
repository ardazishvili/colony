#include "ColonyMouseScrollEvent.h"
#include "../../fig/Camera.h"

ColonyMouseScrollEvent::ColonyMouseScrollEvent(GLFWwindow* window,
                                               double xoffset,
                                               double yoffset) :
  MouseScrollEvent(window, xoffset, yoffset)
{
}

void ColonyMouseScrollEvent::process(Camera* camera, EventManager* m)
{
  camera->zoom(_yoffset);
}
