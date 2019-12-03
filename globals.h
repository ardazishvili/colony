#ifndef GLOBALS_H
#define GLOBALS_H

#include "engine/Camera.h"
#include "engine/ModelLoader.h"
#include "logic/EventManager.h"
#include "logic/Game.h"
#include <glm/glm.hpp>

extern glm::mat4 gView;
extern glm::mat4 gProjection;
extern int currentX;
extern int currentY;
extern float screenWidth;
extern float screenHeight;
extern std::unique_ptr<ModelLoader> modelLoader;
extern Camera camera;
extern Game game;
extern std::unique_ptr<EventManager> eventManager;

#endif
