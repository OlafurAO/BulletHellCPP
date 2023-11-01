#include <Player.h>

Player::~Player() {}

void Player::update() {}

void Player::updateJoystickCrosshair(glm::vec2 movementVector) {
  _crosshair.updateJoystickCrosshair(_equippedWeapon->getHitboxCenterPoint(), movementVector);
}
