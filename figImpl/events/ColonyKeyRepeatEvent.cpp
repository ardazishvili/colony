#include "figImpl/events/ColonyKeyRepeatEvent.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "fig/Camera.h"

ColonyKeyRepeatEvent::ColonyKeyRepeatEvent(int key, int scancode, int mods)
    : KeyboardRepeatEvent(key, scancode, mods) {}

void ColonyKeyRepeatEvent::process(fig::Camera* camera,
                                   fig::EventManager* eventManager) {
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
