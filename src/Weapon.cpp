#include <Weapon.h>

void Weapon::setDirection(int direction) { _direction = direction; }

void Weapon::followCrosshair(glm::vec2 crosshairPos) {
  setZRotation((atan2(crosshairPos.y - _position.y, crosshairPos.x - _position.x) * 180 / M_PI));
}
