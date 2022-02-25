#pragma once

#include <memory>

#include "fig/Model.h"

class View {
 public:
  View(glm::vec3 position);
  virtual ~View() = default;
  View(const View&) = delete;
  View(View&&) = delete;
  View& operator=(const View&) = delete;
  View& operator=(View&&) = delete;

  virtual void draw() = 0;
  virtual glm::vec3 position() const;
  float longitude() const;
  float latitude() const;
  float h(float phi) const;
  float k(float phi) const;
  glm::mat4 flatModel() const;
  glm::mat4 globeModel() const;

  static float VIEW_SCALE;

 protected:
  glm::vec3 globeMapper(glm::vec3 p) const;
  bool _hasAnimation{false};
  std::shared_ptr<fig::Model> _model;
  fig::Shader& _shader;
  glm::vec3 _position;
  float _angle{0.0f};
  float _objScale{1.0f};

  static constexpr float R = 4 * M_PI;
  static constexpr float S = 6 * M_PI;
};
