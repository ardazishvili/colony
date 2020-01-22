#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "../logic/EventManager.h"
#include "../logic/Game.h"
#include "Camera.h"
#include "Light.h"
#include "LinesShader.h"
#include "PhongShader.h"
#include "Skybox.h"
#include "SkyboxShader.h"

class Application
{
public:
  Application();
  Application(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(const Application&) = delete;
  Application& operator=(Application&&) = delete;
  ~Application();

  void run();

  std::unique_ptr<Light> _light;
  std::unique_ptr<EventManager> _eventManager;
  std::unique_ptr<Skybox> _skybox;
  std::unique_ptr<Game> _game;
  std::unique_ptr<PhongShader> _colorShader;
  std::unique_ptr<PhongShader> _colorNonFlatShader;
  std::unique_ptr<PhongShader> _lampShader;
  std::unique_ptr<PhongShader> _textureShader;
  std::unique_ptr<LinesShader> _linesShader;
  std::unique_ptr<SkyboxShader> _skyboxShader;
  std::unique_ptr<AStar> _astar;

  GLFWwindow* _window;
  Camera _camera;
  std::unique_ptr<Terrain> _terrain;

  glm::mat4 _view;
  glm::mat4 _projection;
  float _screenWidth;
  float _screenHeight;

private:
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
};

#endif
