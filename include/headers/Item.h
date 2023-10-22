#pragma once

#include <GameObject.h>

class Item : public GameObject {
public:
  Item(GameObjectType objectType) : GameObject(objectType){};
  ~Item(){};
};
