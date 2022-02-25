#include "logic/structures/AbstractPlant.h"

AbstractPlant::AbstractPlant(std::unique_ptr<AbstractPlantView> view)
    : _view(std::move(view)) {}

void AbstractPlant::render() { _view->draw(); }

glm::vec2 AbstractPlant::position() { return _view->position(); }
