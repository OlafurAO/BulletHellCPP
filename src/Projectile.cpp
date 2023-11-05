#include <Projectile.h>

void Projectile::update(double deltaTime) {
  _position += glm::normalize(_velocityVector) * _speed * (float)deltaTime;
  _hitbox->updatePosition(_position);
  updateAnimator(deltaTime);
}

void Projectile::setVelocityVector(glm::vec2 velocityVector) { _velocityVector = velocityVector; }
