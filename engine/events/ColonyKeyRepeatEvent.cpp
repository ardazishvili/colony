#include "ColonyKeyRepeatEvent.h"
#include "../../logic/EventManager.h"

ColonyKeyRepeatEvent::ColonyKeyRepeatEvent(GLFWwindow* window,
                                           int key,
                                           int scancode,
                                           int mods) :
  KeyboardRepeatEvent(window, key, scancode, mods)
{
}

void ColonyKeyRepeatEvent::process(Camera* camera, EventManager* eventManager)
{
  if (_key == GLFW_KEY_LEFT) {
    camera->rotateLeft();
  }
  if (_key == GLFW_KEY_RIGHT) {
    camera->rotateRight();
  }
  if (_key == GLFW_KEY_W) {
    camera->moveForward();
  }
  if (_key == GLFW_KEY_S) {
    camera->moveBackward();
  }
  if (_key == GLFW_KEY_A) {
    camera->moveLeft();
  }
  if (_key == GLFW_KEY_D) {
    camera->moveRight();
  }
}
