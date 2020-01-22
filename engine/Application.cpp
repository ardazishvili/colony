#include <cstdio>
#include <functional>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../globals.h"
#include "Application.h"
#include "LinesShader.h"
#include "ModelLoader.h"
#include "SkyboxShader.h"

using namespace std::placeholders;

void Application::processInput(GLFWwindow* window)
{
  _camera.updateSpeed();
}

Application* appPtr;
void error_callback(int error, const char* description)
{
  if (appPtr) {
    appPtr->error_cb(error, description);
  }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if (appPtr) {
    appPtr->mouse_cb(window, xpos, ypos);
  }
}

void keyboard_callback(GLFWwindow* window,
                       int key,
                       int scancode,
                       int action,
                       int mods)
{
  if (appPtr) {
    appPtr->keyboard_cb(window, key, scancode, action, mods);
  }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  if (appPtr) {
    appPtr->scroll_cb(window, xoffset, yoffset);
  }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (appPtr) {
    appPtr->mouse_button_cb(window, button, action, mods);
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  if (appPtr) {
    appPtr->mouse_cb(window, width, height);
  }
}

void Application::error_cb(int error, const char* description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void Application::mouse_cb(GLFWwindow* window, double xpos, double ypos)
{
  _eventManager->handleMouseMove(window, xpos, ypos);
}

void Application::keyboard_cb(GLFWwindow* window,
                              int key,
                              int scancode,
                              int action,
                              int mods)
{
  _eventManager->handleKeyPress(window, key, scancode, action, mods);
}

void Application::scroll_cb(GLFWwindow* window, double xoffset, double yoffset)
{
  _camera.zoom(yoffset);
}

void Application::mouse_button_cb(GLFWwindow* window,
                                  int button,
                                  int action,
                                  int mods)
{
  _eventManager->handleMousePressed(button, action);
}

void Application::framebuffer_size_cb(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

Application::Application() :
  _camera(glm::vec3(0.0f, -45.0f, 60.0f),
          glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f))
{
  appPtr = this;
  glfwSetErrorCallback(error_callback);
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
  glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
  glfwSetCursorPosCallback(_window, mouse_callback);
  glfwSetScrollCallback(_window, scroll_callback);
  glfwSetMouseButtonCallback(_window, mouse_button_callback);
  glfwSetKeyCallback(_window, keyboard_callback);

  _light = std::make_unique<Light>(
    glm::vec3(1.2f, 0.0f, 5.0f), _camera, _screenWidth, _screenHeight);
  _colorShader = std::make_unique<PhongShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_color.vs",
    "/home/roman/repos/colony/shaders/fragment_color.fs");
  _colorNonFlatShader = std::make_unique<PhongShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_color_nonflat.vs",
    "/home/roman/repos/colony/shaders/fragment_color_nonflat.fs");
  _textureShader = std::make_unique<PhongShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_objects.vs",
    "/home/roman/repos/colony/shaders/fragment_objects.fs");
  _lampShader = std::make_unique<PhongShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_light.vs",
    "/home/roman/repos/colony/shaders/fragment_light.fs");
  _light->setShader(_lampShader.get());
  _skyboxShader = std::make_unique<SkyboxShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_skybox.vs",
    "/home/roman/repos/colony/shaders/fragment_skybox.fs");
  _linesShader = std::make_unique<LinesShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_lines.vs",
    "/home/roman/repos/colony/shaders/fragment_lines.fs");
  modelLoader = std::make_unique<ModelLoader>(*_textureShader);
  modelLoader->load();

  glEnable(GL_DEPTH_TEST);
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  auto xScale = 2.85f;
  auto yScale = 2.15f;
  auto zScale = 2.0f;
  _terrain = std::make_unique<Terrain>(*_colorShader,
                                       _camera,
                                       -10.0f * xScale,
                                       -10.0f * yScale,
                                       10.0f * xScale,
                                       10.0f * yScale,
                                       256 / 2,
                                       zScale);
  _game = std::make_unique<Game>(_window, _view, _projection);
  _game->addTerrain(_terrain.get());
  auto mapObstacles =
    ::makeObstaclesSegment(*_colorNonFlatShader,
                           _terrain.get(),
                           glm::vec2(-10 * xScale + 0.01, -10 * yScale + 0.01),
                           glm::vec2(10 * xScale - 0.01, 10 * yScale - 0.01));
  _astar = std::make_unique<AStar>(mapObstacles->vertices(),
                                   mapObstacles->obstacles(),
                                   mapObstacles->dimensions());
  _eventManager = std::make_unique<EventManager>(_view,
                                                 _projection,
                                                 _window,
                                                 _game.get(),
                                                 _camera,
                                                 *_textureShader,
                                                 *_colorShader,
                                                 *_colorNonFlatShader,
                                                 *_linesShader,
                                                 _terrain.get(),
                                                 mapObstacles,
                                                 _astar.get());

  createTank(_game.get(),
             *_textureShader,
             *_linesShader,
             _astar.get(),
             _terrain.get()->getXYZ(glm::vec2(0.0, 0.0f)));
  createTank(_game.get(),
             *_textureShader,
             *_linesShader,
             _astar.get(),
             _terrain.get()->getXYZ(glm::vec2(5.0, 5.0f)));
  createTank(_game.get(),
             *_textureShader,
             *_linesShader,
             _astar.get(),
             _terrain.get()->getXYZ(glm::vec2(-5.0, -5.0f)));
  createTank(_game.get(),
             *_textureShader,
             *_linesShader,
             _astar.get(),
             _terrain.get()->getXYZ(glm::vec2(0.0, 5.0f)));
  createTank(_game.get(),
             *_textureShader,
             *_linesShader,
             _astar.get(),
             _terrain.get()->getXYZ(glm::vec2(0.0, -5.0f)));

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  _skybox = std::make_unique<Skybox>(*_skyboxShader);
}

void Application::run()
{
  while (!glfwWindowShouldClose(_window)) {
    glfwPollEvents();
    processInput(_window);

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

    ImGui::Begin("camera");
    static float camera_z = 60.0f;
    ImGui::SetWindowPos(ImVec2(0, 210));
    ImGui::SetWindowSize(ImVec2(500, 50));
    ImGui::SliderFloat("camera z", &camera_z, -100.0f, 100.0f);
    ImGui::End();
    auto eye = _camera.eye();
    eye.z = camera_z;
    _camera.setEye(eye);

    ImGui::Begin("models scale");
    ImGui::SetWindowPos(ImVec2(0, 450));
    ImGui::SetWindowSize(ImVec2(200, 50));
    ImGui::SliderFloat("scale", &View::VIEW_SCALE, 0.0f, 1.0f);
    ImGui::End();

    ImGui::Begin("light");
    static float x = 1.2;
    static float y = 0.0;
    static float z = 90.0;
    ImGui::SetWindowPos(ImVec2(0, 110));
    ImGui::SetWindowSize(ImVec2(500, 100));
    ImGui::SliderFloat("light x", &x, -10.0f, 10.0f);
    ImGui::SliderFloat("light y", &y, -10.0f, 10.0f);
    ImGui::SliderFloat("light z", &z, -100.0f, 100.0f);
    ImGui::End();
    _light->setPosition(glm::vec3(x, y, z));

    _view = glm::lookAt(_camera.eye(), _camera.reference(), _camera.up());
    _projection = glm::perspective(glm::radians(_camera.fov()),
                                   _screenWidth / _screenHeight,
                                   0.01f,
                                   1000.0f);

    _terrain.get()->render();

    _eventManager->tick();

    _skybox.get()->render();

    /* auto s = Sphere(colorShader, glm::vec3(0.0f, 0.0f, 5.0f), 1.0f, 50); */
    /* s.render(); */

    _terrain.get()->renderSub();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glBindVertexArray(0);
    glfwSwapBuffers(_window);
  }
}

Application::~Application()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(_window);
  glfwTerminate();
}
