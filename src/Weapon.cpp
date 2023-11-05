#include <Weapon.h>

void Weapon::initBaselineProjectile() { _baselineProjectile = Projectile(GameObjectType::PROJECTILE, 1.f); }

void Weapon::registerProjectileTexture(const char* texKey, Texture2D& tex, SDL_Renderer* renderer, unsigned int referenceFrameIndex) {
  _baselineProjectile.registerTexture(texKey, tex, renderer, referenceFrameIndex);
}

void Weapon::setDirection(int direction) { _direction = direction; }

void Weapon::followCrosshair(glm::vec2 crosshairPos) {
  setZRotation((atan2(crosshairPos.y - _position.y, crosshairPos.x - _position.x) * 180 / M_PI));
}

void Weapon::fireWeapon(glm::vec2 crossHairPos) {
  glm::vec2 startLocation = getHitboxCenterPoint();
  glm::vec2 velocity = glm::vec2(crossHairPos.x - startLocation.x, crossHairPos.y - startLocation.y);

  Projectile newProjectile = _baselineProjectile;
  newProjectile.setPosition(startLocation);
  newProjectile.setVelocityVector(velocity);

  _projectileQueue.push_back(newProjectile);
}

void Weapon::clearProjectileQueue() { _projectileQueue.clear(); }

std::vector<Projectile*> Weapon::getNewProjectiles() {
  std::vector<Projectile*> newProjectiles;

  for (Projectile proj : _projectileQueue) {
    newProjectiles.push_back(&proj);
  }

  return newProjectiles;
}
