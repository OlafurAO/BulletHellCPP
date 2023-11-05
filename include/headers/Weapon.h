#pragma once

#include <math.h>
#include <vector>

#include <glm/glm.hpp>

#include <GameObject.h>
#include <Projectile.h>

class Weapon : public GameObject {
public:
  Weapon(GameObjectType objectType) : GameObject(objectType) {}
  Weapon(GameObjectType objectType, float scale) : GameObject(objectType, scale) {}
  ~Weapon(){};

  void initBaselineProjectile();
  void registerProjectileTexture(const char* texKey, Texture2D& tex, SDL_Renderer* renderer, unsigned int referenceFrameIndex);

  void setDirection(int direction);
  void followCrosshair(glm::vec2 crosshairPos);

  void fireWeapon(glm::vec2 crossHairPos);

  void clearProjectileQueue();

  std::vector<Projectile*> getNewProjectiles();

private:
  std::vector<Projectile> _projectileQueue;
  Projectile _baselineProjectile;
};
