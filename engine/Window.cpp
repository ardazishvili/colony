#include <cstdio>
#include <iomanip>

#include "../globals.h"
#include "Window.h"
#include "events/ColonyErrorEvent.h"
/* #include "events/ColonyKeyPressEvent.h" */
/* #include "events/ColonyKeyReleaseEvent.h" */
/* #include "events/ColonyKeyRepeatEvent.h" */
/* #include "events/ColonyMouseMoveEvent.h" */
/* #include "events/ColonyMousePressEvent.h" */
/* #include "events/ColonyMouseReleaseEvent.h" */
/* #include "events/ColonyMouseScrollEvent.h" */
#include "events/EventFabric.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

std::function<void(std::unique_ptr<Event> event)> Window::_onEvent =
  [](std::unique_ptr<Event> event) {
  };
EventFabric* Window::_eventFabric = nullptr;

Window::Window(glm::mat4& view,
               glm::mat4& projection,
               std::function<void(std::unique_ptr<Event> event)> onEvent,
               EventFabric* eventFabric) :
  _view(view),
  _projection(projection)
{
  _eventFabric = eventFabric;
  _onEvent = onEvent;
  glfwInit();
  const char* glsl_version = "#version 450";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  int count;
  GLFWmonitor** monitors = glfwGetMonitors(&count);
  const GLFWvidmode* mode = glfwGetVideoMode(monitors[1]);
  _screenWidth = mode->width;
  _screenHeight = mode->height - 150;
  _window =
    glfwCreateWindow(_screenWidth, _screenHeight, "LearnOPenGl", NULL, NULL);
  if (_window == NULL) {
    glfwTerminate();
    throw "Application ctor failed: failed to create window";
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(_window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  ImGui::GetStyle().WindowRounding = 0.0f;
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1);

  auto err = glewInit();
  if (err) {
    throw "Application ctor failed: Failed to initialize OpenGL loader!";
  }

  glViewport(0, 0, _screenWidth, _screenHeight);

  glfwSetErrorCallback([](int, const char*) {
    _onEvent(std::make_unique<ErrorEvent>());
  });

  glfwSetFramebufferSizeCallback(_window,
                                 [](GLFWwindow* window, int width, int height) {
                                   glViewport(0, 0, width, height);
                                 });

  glfwSetCursorPosCallback(
    _window, [](GLFWwindow* window, double xpos, double ypos) {
      _onEvent(_eventFabric->getMouseMoveEvent(window, xpos, ypos));
    });

  glfwSetScrollCallback(
    _window, [](GLFWwindow* window, double xoffset, double yoffset) {
      _onEvent(_eventFabric->getMouseScrollEvent(window, xoffset, yoffset));
    });

  glfwSetMouseButtonCallback(
    _window, [](GLFWwindow* window, int button, int action, int mods) {
      switch (action) {
        case GLFW_PRESS:
          _onEvent(
            _eventFabric->getMousePressedEvent(window, button, action, mods));
          break;
        case GLFW_RELEASE:
          _onEvent(
            _eventFabric->getMouseReleasedEvent(window, button, action, mods));
          break;
      }
    });

  glfwSetKeyCallback(
    _window,
    [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      switch (action) {
        case GLFW_PRESS:
          _onEvent(_eventFabric->getKeyPressEvent(window, key, scancode, mods));
          break;
        case GLFW_RELEASE:
          _onEvent(
            _eventFabric->getKeyReleaseEvent(window, key, scancode, mods));
          break;
        case GLFW_REPEAT:
          _onEvent(
            _eventFabric->getKeyRepeatEvent(window, key, scancode, mods));
          break;
      }
    });

  glEnable(GL_DEPTH_TEST);
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
}

Window::~Window()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(_window);
  glfwTerminate();
}

float Window::width() const
{
  return _screenWidth;
}

float Window::height() const
{
  return _screenHeight;
}

void Window::preUpdate()
{
  glfwPollEvents();
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  logger.render();

  int display_w, display_h;
  glfwGetFramebufferSize(_window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glm::vec4 clear_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.00f);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
}

void Window::postUpdate()
{

  showDebug();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  glBindVertexArray(0);
  glfwSwapBuffers(_window);
}

void Window::showDebug()
{
  auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
               ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs;
  ImGui::Begin("3dCoordinates", NULL, flags);
  ImGui::SetWindowPos(ImVec2(0, _screenHeight - 22));
  ImGui::SetWindowSize(ImVec2(500, 22));
  auto pos = EventManager::unProject(this, _view, _projection);
  std::stringstream ss;
  ss << "x:" << std::setw(5) << std::setprecision(2) << pos.x
     << "; y:" << std::setw(5) << std::setprecision(2) << pos.y
     << "; z: " << pos.z;
  ImGui::Text(ss.str().c_str());
  ImGui::End();
}

void Window::getCursorPos(double* xpos, double* ypos) const
{
  glfwGetCursorPos(_window, xpos, ypos);
}
