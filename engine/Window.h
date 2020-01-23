#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "../logic/EventManager.h"
#include "Camera.h"
#include "events/Event.h"

class Window
{
public:
  Window(std::unique_ptr<EventManager>& em,
         Camera& c,
         glm::mat4& view,
         glm::mat4& projection,
         std::function<void(Event& event)> onEvent);
  Window(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(const Window&) = delete;
  Window& operator=(Window&&) = delete;
  ~Window();

  void preUpdate();
  void postUpdate();
  float width() const;
  float height() const;
  void getCursorPos(double* xpos, double* ypos) const;

  GLFWwindow* _window;

private:
  void showDebug();
  void error_cb(int error, const char* description);
  void mouse_cb(GLFWwindow* window, double xpos, double ypos);
  void keyboard_cb(GLFWwindow* window,
                   int key,
                   int scancode,
                   int action,
                   int mods);
  void scroll_cb(GLFWwindow* window, double xoffset, double yoffset);
  void mouse_button_cb(GLFWwindow* window, int button, int action, int mods);
  void framebuffer_size_cb(GLFWwindow* window, int width, int height);
  void processInput(GLFWwindow* window);
  friend void error_callback(int, const char*);
  friend void mouse_callback(GLFWwindow*, double, double);
  friend void keyboard_callback(GLFWwindow*, int, int, int, int);
  friend void scroll_callback(GLFWwindow*, double, double);
  friend void mouse_button_callback(GLFWwindow*, int, int, int);
  friend void framebuffer_size_callback(GLFWwindow*, int, int);

  float _screenWidth;
  float _screenHeight;
  std::unique_ptr<EventManager>& _eventManager;
  Camera& _camera;
  glm::mat4& _view;
  glm::mat4& _projection;

  static std::function<void(Event& event)> _onEvent;
};

#endif
