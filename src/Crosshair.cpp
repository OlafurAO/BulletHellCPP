#include <Crosshair.h>

Crosshair::Crosshair() : _position(glm::vec2(0, 0)){};

Crosshair::~Crosshair() {}

void Crosshair::updatePosition(int x, int y) { _position = glm::vec2(x, y); }

glm::vec2 Crosshair::getPositionVec() { return _position; }

#include <iostream>
void Crosshair::updateJoystickCrosshair(glm::vec2 weaponPos, glm::vec2 movementVector) {
  std::cout << movementVector.x << ", " << movementVector.y << std::endl;
  glm::vec2 newPos = _position + movementVector * 0.05f;
  if (newPos.x >= (weaponPos.x - _joystickRadius) && newPos.x <= (weaponPos.x + _joystickRadius)) {
    _position.x = newPos.x;
  }

  if (newPos.y >= (weaponPos.y - _joystickRadius) && newPos.y <= (weaponPos.y + _joystickRadius)) {
    _position.y = newPos.y;
  }

  return;
  // angle = std::atan2(movementVector.x * 0.0001, movementVector.y * 0.0001) * 180 / M_PI;
  // angle += 0.001;
  // _position = glm::vec2(weaponPos.x + _joystickRadius * cos(angle), weaponPos.y + _joystickRadius * sin(angle));
}
