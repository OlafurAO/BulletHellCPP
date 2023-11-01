#pragma once

#include <cmath>

#include <glm/glm.hpp>

class Crosshair {
public:
  Crosshair();
  ~Crosshair();

  void updatePosition(int x, int y);
  glm::vec2 getPositionVec();

  void updateJoystickCrosshair(glm::vec2 weaponPos, glm::vec2 movementVector);

private:
  const float _joystickRadius = 30.f;
  glm::vec2 _position;
};
