#include <cstdio>
#include <functional>

#include "../fig/imgui/imgui.h"
#include "../fig/imgui/imgui_impl_glfw.h"
#include "../fig/imgui/imgui_impl_opengl3.h"

#include "../fig/globals.h"
#include "ColonyApplication.h"
#include "GameLayer.h"
#include "GuiLayer.h"
#include "events/ColonyEventFabric.h"

using namespace std::placeholders;

ColonyApplication::ColonyApplication() :
  _camera(glm::vec3(0.0f, -45.0f, 60.0f),
          glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f))
{
  _onEvent = [this](std::unique_ptr<Event> event) {
    event->process(&_camera, _eventManager);
  };
  _eventFabric = std::make_unique<ColonyEventFabric>();
  /* int count; */
  /* GLFWmonitor** monitors = glfwGetMonitors(&count); */
  /* const GLFWvidmode* mode = glfwGetVideoMode(monitors[1]); */
  int screenWidth = 1920;
  int screenHeight = 1200 - 150;
  Window::Param param = { screenWidth, screenHeight };
  _window = std::make_unique<ColonyWindow>(
    _view, _projection, _eventFabric.get(), param);

  /* ImGui_ImplOpenGL3_NewFrame(); */
  /* ImGui_ImplGlfw_NewFrame(); */
  /* ImGui::NewFrame(); */

  auto gameLayer =
    std::make_unique<GameLayer>(_window.get(), &_camera, _view, _projection);
  gameLayer->init();
  _window->setOnEvent(gameLayer->onEvent());
  addLayer(std::move(gameLayer));

  auto guiLayer =
    std::make_unique<GuiLayer>(param, _window.get(), _view, _projection);
  guiLayer->init();
  addLayer(std::move(guiLayer));

  /* ImGui::Render(); */
  /* ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); */
}

void ColonyApplication::run()
{
  while (!glfwWindowShouldClose(_window->_window)) {

    _window->preUpdate();

    update();
    render();
    _window->postUpdate();

    /* ImGui::Render(); */
    /* ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); */
  }
}

