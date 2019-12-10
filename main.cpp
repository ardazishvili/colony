#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "engine/Light.h"
#include "engine/LinesShader.h"
#include "engine/PhongShader.h"
#include "engine/Skybox.h"
#include "engine/SkyboxShader.h"
#include "engine/Sphere.h"
#include "engine/Terrain.h"

#include "logic/EventManager.h"
#include "logic/Game.h"

#include "globals.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

static void glfw_error_callback(int error, const char* description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void processInput(GLFWwindow* window)
{
  camera.updateSpeed();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  currentX = xpos;
  currentY = ypos;
  eventManager->handleMouseMove(window, xpos, ypos);
  /* camera.tilt(xpos, ypos); */
}

void keyboard_callback(GLFWwindow* window,
                       int key,
                       int scancode,
                       int action,
                       int mods)
{
  eventManager->handleKeyPress(window, key, scancode, action, mods);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  camera.zoom(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  eventManager->handleMousePressed(button, action);
}

int main(int argc, char** argv)
{
  glfwSetErrorCallback(glfw_error_callback);
  glfwInit();
  const char* glsl_version = "#version 450";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  int count;
  GLFWmonitor** monitors = glfwGetMonitors(&count);
  const GLFWvidmode* mode = glfwGetVideoMode(monitors[1]);
  screenWidth = mode->width - 200;
  screenHeight = mode->height - 200;
  GLFWwindow* window =
    glfwCreateWindow(screenWidth, screenHeight, "LearnOPenGl", NULL, NULL);
  if (window == NULL) {
    std::cout << "failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  bool show_demo_window = true;
  ImGui::GetStyle().WindowRounding = 0.0f;
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  auto err = glewInit();
  if (err) {
    fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    return 1;
  }

  glm::vec4 clear_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.00f);
  glViewport(0, 0, screenWidth, screenHeight);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetKeyCallback(window, keyboard_callback);

  PhongShader colorShader("/home/roman/repos/colony/shaders/vertex_color.vs",
                          "/home/roman/repos/colony/shaders/fragment_color.fs");
  PhongShader textureShader(
    "/home/roman/repos/colony/shaders/vertex_objects.vs",
    "/home/roman/repos/colony/shaders/fragment_objects.fs");
  PhongShader lampShader("/home/roman/repos/colony/shaders/vertex_light.vs",
                         "/home/roman/repos/colony/shaders/fragment_light.fs");
  SkyboxShader skyboxShader(
    "/home/roman/repos/colony/shaders/vertex_skybox.vs",
    "/home/roman/repos/colony/shaders/fragment_skybox.fs");
  LinesShader linesShader("/home/roman/repos/colony/shaders/vertex_lines.vs",
                          "/home/roman/repos/colony/shaders/fragment_lines.fs");
  modelLoader = std::make_unique<ModelLoader>(textureShader);
  modelLoader->load();

  glEnable(GL_DEPTH_TEST);
  light = std::make_unique<Light>(
    glm::vec3(1.2f, 0.0f, 5.0f), lampShader, camera, screenWidth, screenHeight);
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  auto xyScale = 2.0f;
  auto zScale = 3.0f;
  auto terrain = Terrain(
    colorShader, -10.0f, -10.0f, 10.0f, 10.0f, 256 * 1, xyScale, zScale);
  game.addTerrain(&terrain);
  eventManager = std::make_unique<EventManager>(
    window, game, camera, textureShader, colorShader, &terrain);

  createTank(game, textureShader, terrain.getXYZ(glm::vec2(0.0, 0.0f)));
  /* createTank(game, textureShader, terrain.getXYZ(glm::vec2(1.0, -1.0f))); */
  /* createTank(game, textureShader, terrain.getXYZ(glm::vec2(2.0, -2.0f))); */
  /* auto tankFactory = */
  /*   std::make_shared<TankFactory>(textureShader, glm::vec2(2.0f, 2.0f)); */
  /* game.addStructure(tankFactory); */
  /* tankFactory->commit(); */

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  auto skybox = Skybox(skyboxShader);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    processInput(window);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

    ImGui::Begin("camera");
    static float camera_z = 20.0f;
    ImGui::SetWindowPos(ImVec2(0, 210));
    ImGui::SetWindowSize(ImVec2(500, 100));
    ImGui::SliderFloat("camera z", &camera_z, 0.0f, 20.0f);
    ImGui::End();
    auto eye = camera.eye();
    eye.z = camera_z;
    camera.setEye(eye);

    ImGui::Begin("models scale");
    ImGui::SetWindowPos(ImVec2(0, 620));
    ImGui::SetWindowSize(ImVec2(200, 50));
    ImGui::SliderFloat("scale", &View::VIEW_SCALE, 0.0f, 1.0f);
    ImGui::End();

    ImGui::Begin("light");
    static float x = 1.2;
    static float y = 0.0;
    static float z = 10.0;
    ImGui::SetWindowPos(ImVec2(0, 110));
    ImGui::SetWindowSize(ImVec2(500, 100));
    ImGui::SliderFloat("light x", &x, -10.0f, 10.0f);
    ImGui::SliderFloat("light y", &y, -10.0f, 10.0f);
    ImGui::SliderFloat("light z", &z, -10.0f, 100.0f);
    ImGui::End();
    light->setPosition(glm::vec3(x, y, z));

    glm::mat4 view = glm::lookAt(camera.eye(), camera.reference(), camera.up());
    glm::mat4 projection = glm::perspective(
      glm::radians(camera.fov()), screenWidth / screenHeight, 0.01f, 1000.0f);
    gView = view;
    gProjection = projection;

    /* linesShader.configureRender(); */

    terrain.render();

    eventManager->tick();

    /* skybox.render(); */

    auto s = Sphere(colorShader, glm::vec3(0.0f, 0.0f, 5.0f), 1.0f, 30);
    s.render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glBindVertexArray(0);
    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
