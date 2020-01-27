#include <cstdio>
#include <iomanip>

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
                           EventFabric* eventFabric) :
  _view(view),
  _projection(projection)
{
  _eventFabric = eventFabric;
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
  return _screenWidth;
}

float ColonyWindow::height() const
{
  return _screenHeight;
}

void ColonyWindow::preUpdate()
{
  glfwPollEvents();
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  logger.render();

  /* ImGui::Begin("camera"); */
  /* static float camera_z = 60.0f; */
  /* ImGui::SetWindowPos(ImVec2(0, 210)); */
  /* ImGui::SetWindowSize(ImVec2(500, 50)); */
  /* ImGui::SliderFloat("camera z", &camera_z, -100.0f, 100.0f); */
  /* ImGui::End(); */
  /* auto eye = _camera.eye(); */
  /* eye.z = camera_z; */
  /* _camera.setEye(eye); */

  ImGui::Begin("models scale");
  ImGui::SetWindowPos(ImVec2(0, 450));
  ImGui::SetWindowSize(ImVec2(200, 50));
  ImGui::SliderFloat("scale", &View::VIEW_SCALE, 0.0f, 1.0f);
  ImGui::End();

  /* ImGui::Begin("light"); */
  /* static float x = 1.2; */
  /* static float y = 0.0; */
  /* static float z = 90.0; */
  /* ImGui::SetWindowPos(ImVec2(0, 110)); */
  /* ImGui::SetWindowSize(ImVec2(500, 100)); */
  /* ImGui::SliderFloat("light x", &x, -10.0f, 10.0f); */
  /* ImGui::SliderFloat("light y", &y, -10.0f, 10.0f); */
  /* ImGui::SliderFloat("light z", &z, -100.0f, 100.0f); */
  /* ImGui::End(); */
  /* _light->setPosition(glm::vec3(x, y, z)); */

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

  showDebug();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  glBindVertexArray(0);
  glfwSwapBuffers(_window);
}

void ColonyWindow::showDebug()
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

void ColonyWindow::getCursorPos(double* xpos, double* ypos) const
{
  glfwGetCursorPos(_window, xpos, ypos);
}

void ColonyWindow::setOnEvent(
  std::function<void(std::unique_ptr<Event> event)> onEvent)
{
  _onEvent = onEvent;
}
