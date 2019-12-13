#include "globals.h"

/* glm::mat4 gView; */
/* glm::mat4 gProjection; */
/* int currentX; */
/* int currentY; */
/* float screenWidth; */
/* float screenHeight; */

std::unique_ptr<ModelLoader> modelLoader;
/* Camera camera(glm::vec3(0.0f, -15.0f, 15.0f), */
/*               glm::vec3(0.0f, 0.0f, 0.0f), */
/*               glm::vec3(0.0f, 0.0f, 1.0f)); */
std::unique_ptr<Game> game;
std::unique_ptr<Light> light;
std::unique_ptr<EventManager> eventManager;
