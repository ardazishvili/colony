#include <cstdio>

#include "../fig/events/EventFabric.h"
#include "../fig/globals.h"
#include "ColonyWindow.h"
#include "events/ColonyErrorEvent.h"

#include "../fig/imgui/imgui.h"
#include "../fig/imgui/imgui_impl_glfw.h"
#include "../fig/imgui/imgui_impl_opengl3.h"

std::function<void(std::unique_ptr<Event> event)> ColonyWindow::_onEvent =
  [](std::unique_ptr<Event> event) {
  };
EventFabric* ColonyWindow::_eventFabric = nullptr;

ColonyWindow::ColonyWindow(glm::mat4& view,
                           glm::mat4& projection,
                           EventFabric* eventFabric,
                           const Window::Param& param) :
  Window(param),
  _view(view), _projection(projection)
{
  _eventFabric = eventFabric;
  glfwInit();
  const char* glsl_version = "#version 450";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  /* int count; */
  /* GLFWmonitor** monitors = glfwGetMonitors(&count); */
  /* const GLFWvidmode* mode = glfwGetVideoMode(monitors[1]); */
  /* _param.width = mode->width; */
  /* _param.height = mode->height - 150; */
  /* std::cout << "_param.width= " << _param.width << std::endl; */
  /* std::cout << "_param.height= " << _param.height << std::endl; */
  _window =
    glfwCreateWindow(_param.width, _param.height, "LearnOPenGl", NULL, NULL);

  if (_window == NULL) {
    glfwTerminate();
    throw "Application ctor failed: failed to create window";
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
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

  glViewport(0, 0, _param.width, _param.height);

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

ColonyWindow::~ColonyWindow()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(_window);
  glfwTerminate();
}

float ColonyWindow::width() const
{
  return _param.width;
}

float ColonyWindow::height() const
{
  return _param.height;
}

void ColonyWindow::preUpdate()
{
  glfwPollEvents();
  /* ImGui_ImplOpenGL3_NewFrame(); */
  /* ImGui_ImplGlfw_NewFrame(); */
  /* ImGui::NewFrame(); */

  int display_w, display_h;
  glfwGetFramebufferSize(_window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glm::vec4 clear_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.00f);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
}

void ColonyWindow::postUpdate()
{

  /* ImGui::Render(); */
  /* ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); */
  glBindVertexArray(0);
  glfwSwapBuffers(_window);
}

void ColonyWindow::getCursorPos(double* xpos, double* ypos) const
{
  glfwGetCursorPos(_window, xpos, ypos);
}

void ColonyWindow::setOnEvent(
  std::function<void(std::unique_ptr<Event> event)> onEvent)
{
  _onEvent = onEvent;
}
