#pragma once

#include <GameObject.h>
#include <glm/glm.hpp>
#include <math.h>

class Weapon : public GameObject {
public:
  Weapon(GameObjectType objectType) : GameObject(objectType) {}
  Weapon(GameObjectType objectType, float scale) : GameObject(objectType, scale) {}
  ~Weapon(){};

  void setDirection(int direction);
  void followCrosshair(glm::vec2 crosshairPos);

private:
};
