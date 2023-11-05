#pragma once

#include <glm/glm.hpp>

#include <Enums.h>
#include <GameObject.h>

class Projectile : public GameObject {
public:
  Projectile() : GameObject(){};
  Projectile(GameObjectType objectType, float scale) : GameObject(objectType, scale){};

  void update(double deltaTime) override;
  void setVelocityVector(glm::vec2 velocityVector);

private:
  glm::vec2 _velocityVector;
};
