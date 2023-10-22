#pragma once

#include <GameObject.h>

class Weapon : public GameObject {
public:
  Weapon(GameObjectType objectType) : GameObject(objectType) {}
  Weapon(GameObjectType objectType, float scale) : GameObject(objectType, scale) {}
  ~Weapon(){};

  void setDirection(int direction);

private:
};
