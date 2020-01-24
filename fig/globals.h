#ifndef GLOBALS_H
#define GLOBALS_H

#include "ModelLoader.h"
#include "misc/Logger.h"

extern std::unique_ptr<ModelLoader> modelLoader;
extern Logger logger;
extern bool flatView;

#endif
