#include <iostream>
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
#include "engine/Mesh.h"
#include "engine/PhongShader.h"
#include "engine/Surface.h"

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
  camera.tilt(xpos, ypos);
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

  modelLoader = std::make_unique<ModelLoader>();
  modelLoader->load();
  glm::vec4 clear_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.00f);
  glViewport(0, 0, screenWidth, screenHeight);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetKeyCallback(window, keyboard_callback);

  PhongShader phongShader(
    "/home/roman/repos/opengl/shaders/vertex_objects.vs",
    "/home/roman/repos/opengl/shaders/fragment_objects.fs");
  Shader lampShader("/home/roman/repos/opengl/shaders/vertex_light.vs",
                    "/home/roman/repos/opengl/shaders/fragment_light.fs");

  glEnable(GL_DEPTH_TEST);
  auto light = Light(
    glm::vec3(1.2f, 0.0f, 5.0f), lampShader, camera, screenWidth, screenHeight);
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  /* createTank(game, phongShader, glm::vec2(-0.2f, -3.6f)); */
  /* createTank(game, phongShader, glm::vec2(-2.5f, -2.5f)); */
  /* createTank(game, phongShader, glm::vec2(-5.0f, -5.0f)); */
  /* auto tankFactory = */
  /*   std::make_shared<TankFactory>(phongShader, glm::vec2(2.0f, 2.0f)); */
  /* game.addStructure(tankFactory); */
  /* tankFactory->commit(); */
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  eventManager =
    std::make_unique<EventManager>(window, game, camera, phongShader);
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

    ImGui::Begin("light");
    static float x = 1.2;
    static float y = 0.0;
    static float z = 5.0;
    ImGui::SetWindowPos(ImVec2(0, 100));
    ImGui::SetWindowSize(ImVec2(500, 100));
    ImGui::SliderFloat("light x", &x, -10.0f, 10.0f);
    ImGui::SliderFloat("light y", &y, -10.0f, 10.0f);
    ImGui::SliderFloat("light z", &z, -10.0f, 100.0f);
    ImGui::End();
    light.setPosition(glm::vec3(x, y, z));

    /* ImGui::Begin("camera"); */
    /* static float camera_x = 0.0; */
    /* static float camera_y = -15.0; */
    /* static float camera_z = 15.0; */
    /* static float camera_yaw = 90.0; */
    /* static float camera_pitch = -45.0; */
    /* static float camera_front_x = 0.0; */
    /* static float camera_front_y = 0.7; */
    /* static float camera_front_z = -0.7; */
    /* ImGui::SetWindowPos(ImVec2(0, 200)); */
    /* ImGui::SetWindowSize(ImVec2(500, 230)); */
    /* ImGui::SliderFloat("camera x", &camera_x, -15.0f, 15.0f); */
    /* ImGui::SliderFloat("camera y", &camera_y, -15.0f, 15.0f); */
    /* ImGui::SliderFloat("camera z", &camera_z, -15.0f, 15.0f); */
    /* ImGui::SliderFloat("camera yaw", &camera_yaw, -180.0f, 180.0f); */
    /* ImGui::SliderFloat("camera pitch", &camera_pitch, -180.0f, 180.0f); */
    /* ImGui::SliderFloat("camera front x", &camera_front_x, -M_PI, M_PI); */
    /* ImGui::SliderFloat("camera front y", &camera_front_y, -M_PI, M_PI); */
    /* ImGui::SliderFloat("camera front z", &camera_front_z, -M_PI, M_PI); */
    /* ImGui::End(); */

    /* camera._yaw = camera_yaw; */
    /* camera._pitch = camera_pitch; */
    /* camera._front = glm::vec3(camera_front_x, camera_front_y,
     * camera_front_z); */
    /* camera.updateFront(); */
    /* camera._position = glm::vec3(camera_x, camera_y, camera_z); */
    glm::mat4 view = glm::lookAt(camera.eye(), camera.reference(), camera.up());
    glm::mat4 projection = glm::perspective(
      glm::radians(camera.fov()), screenWidth / screenHeight, 0.01f, 1000.0f);
    gView = view;
    gProjection = projection;

    phongShader.use();
    phongShader.configure(
      light.position(), camera.reference(), view, projection);

    auto surface = Surface(phongShader, -7.0f, -7.0f, 7.0f, 7.0f, 128);
    surface.render();
    /* eventManager->tick(); */

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
